#include "NetReport.h"
#include "dbConnect.h"
#include "SendPing.h"

extern int verbose;

UnitInfoRec::UnitInfoRec()
{
	ZbPing = 0;
	PnPing = 0;
}

UnitInfoRec::~UnitInfoRec()
{
	;
}

NetReport::NetReport()
{
	if (verbose) printf("Start DB\n");
	dbConn = PQconnectdb(connection_str());
	if (PQstatus(dbConn) == CONNECTION_BAD) 
	{
		fprintf(stderr, "Connection to %s failed, %s", connection_str(),
			PQerrorMessage(dbConn));
		throw -1;
	}
}

NetReport::~NetReport()
{
	PQfinish(dbConn);
}

int NetReport::ReadDb(int zigbee)
{
	if (zigbee)
		ReadDbAll();
	else
		ReadDbNew();
}

int NetReport::ReadDbNew()
{
	int i, n;
	int nFields, nTuples;
	PGresult * res;
	char ncmd[1024];
	
	//                    0     1     2     3      4      5  
	sprintf(ncmd, "select unit, appt, name, dinip, wapip, modbip from adomis_box where modbip is not null order by unit;");

	/* Start a transaction block */
	res = PQexec(dbConn, "BEGIN");
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(dbConn));
		PQclear(res);
		return -1;
	}

	/* Should PQclear PGresult whenever it is no longer needed to avoid memory leaks */
	if (verbose) printf("%s\n", ncmd);
	PQclear(res);
	res = PQexec(dbConn, ncmd);
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "Database select failed: %s\n", PQerrorMessage(dbConn));
		PQclear(res);
		return -1;
	}

	/* Print out the attribute names */
	nFields = PQnfields(res);
	nTuples = PQntuples(res);

	/* Print out the rows */
	n = PQntuples(res);
	if (verbose) printf("%d rows\n", n);
	for (i = 0; i < n; i++)
	{
		UnitInfo.UnitNum = atoi(PQgetvalue(res, i, 0));					// 0 - Unit number
		strcpy(UnitInfo.ZbIp, PQgetvalue(res, i, 1));					// 1 - Zigbee gateway IP addres
		strcpy(UnitInfo.UnitName, PQgetvalue(res, i, 2));				// 2 - Unit description
		strcpy(UnitInfo.Resdnt, PQgetvalue(res, i, 3));					// 3 - Resident name
		strcpy(UnitInfo.PnIp, PQgetvalue(res, i, 4));					// 4 - Panel IP address
		strcpy(UnitInfo.ZbIp, PQgetvalue(res, i, 5));					// 5 - Regal alarm IP address
		UnitInfo.Zigbee = false;
		UnitsInfo.push_back(UnitInfo);
		if (verbose) printf("%d :\tUnit %-6d (IP %s)\n", i+1, UnitInfo.UnitNum, UnitInfo.ZbIp);
	}

	PQfinish(dbConn);
	return 0;
}

int NetReport::ReadDbAll()
{
	int i, n;
	int nFields, nTuples;
	PGresult * res;
	char ncmd[1024];
	
	//                    0     1   2     3     4      5      6
	sprintf(ncmd, "select unit, ip, appt, name, dinip, wapip, modbip from adomis_box order by unit;");

	/* Start a transaction block */
	res = PQexec(dbConn, "BEGIN");
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(dbConn));
		PQclear(res);
		return -1;
	}

	/* Should PQclear PGresult whenever it is no longer needed to avoid memory leaks */
	if (verbose) printf("%s\n", ncmd);
	PQclear(res);
	res = PQexec(dbConn, ncmd);
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "Database select failed: %s\n", PQerrorMessage(dbConn));
		PQclear(res);
		return -1;
	}

	/* Print out the attribute names */
	nFields = PQnfields(res);
	nTuples = PQntuples(res);

	/* Print out the rows */
	n = PQntuples(res);
	if (verbose) printf("%d rows\n", n);
	for (i = 0; i < n; i++)
	{
		UnitInfo.UnitNum = atoi(PQgetvalue(res, i, 0));					// 0 - Unit number
		strcpy(UnitInfo.UnitName, PQgetvalue(res, i, 2));				// 2 - Unit description
		strcpy(UnitInfo.Resdnt, PQgetvalue(res, i, 3));					// 3 - Resident name
		strcpy(UnitInfo.ZbIp, PQgetvalue(res, i, 1));					// 1 - Zigbee gateway IP addres
		UnitInfo.Zigbee = true;
		if (strlen(UnitInfo.ZbIp) == 0) 
		{
			strcpy(UnitInfo.ZbIp, PQgetvalue(res, i, 6));	// 6 - Regal alarm IP address
			UnitInfo.Zigbee = false;
		}
		strcpy(UnitInfo.PnIp, PQgetvalue(res, i, 4));					// 4 - Panel IP address
		UnitsInfo.push_back(UnitInfo);
		if (verbose) printf("%d :\tUnit %-6d (IP %s)\n", i+1, UnitInfo.UnitNum, UnitInfo.ZbIp);
	}

	PQfinish(dbConn);
	return 0;
}

int NetReport::List()
{
	int i, n;
	
	n = UnitsInfo.size();
	for(i=0; i<n; i++)
	{
		printf("%3d: Alarm %s, Panel %s\n", i+1, UnitsInfo[i].ZbIp, UnitsInfo[i].PnIp);
	}
	return n;
}

void NetReport::Nmap(const char * descr, char *Ip)
{
	char nmapCmd[256];

	if (verbose)
	{
		printf("Scan %s %s\n", descr, Ip);
		sprintf(nmapCmd, "/usr/bin/nmap -PT1000,5000 %s", Ip);
	}
	else
		sprintf(nmapCmd, "/usr/bin/nmap -PT1000,5000 %s >/dev/null 2>&1", Ip);
	system(nmapCmd);
}

int NetReport::PingIp(const char * descr, char *Ip)
{
	int rc;
	
	if (verbose) printf("Send ping %s %s\n", descr, Ip);
	rc = SendPing(Ip);
	if (verbose) printf("Result of ping %s was %d\n", Ip, rc);
	return rc;
}

void NetReport::Ping(const char * descr, char *Ip)
{
	char pingCmd[256];

	if (verbose)
	{
		printf("Ping %s %s\n", descr, Ip);
		sprintf(pingCmd, "/bin/ping -c 1 -W 1 %s", Ip);
	}
	else
		sprintf(pingCmd, "/bin/ping -c 1 -W 1 %s >/dev/null 2>&1", Ip);
	system(pingCmd);
}

int NetReport::CheckIp(int pflag)
{
	int i, n;
	
	n = UnitsInfo.size();
	for(i=0; i<n; i++)
	{
		UnitsInfo[i].ZbPing = PingIp("Alarm", UnitsInfo[i].ZbIp); 
		/* Only ping panel when required and possible */
		if (pflag && strlen(UnitsInfo[i].PnIp) && 0 != strcmp(UnitsInfo[i].PnIp, "0.0.0.0"))
		{
			UnitsInfo[i].PnPing = PingIp("Panel", UnitsInfo[i].PnIp); 
		}
	}
	return n;
}

int NetReport::ReCheckIp()
{
	int i, n;
	
	n = UnitsInfo.size();
	for(i=0; i<n; i++)
	{
		if (UnitsInfo[i].ZbPing <= 0)
			UnitsInfo[i].ZbPing = PingIp("Retry Alarm", UnitsInfo[i].ZbIp); 
	}
	return n;
}

int NetReport::CheckAll(int usenmap, int pflag)
{
	int i, n;
	
	n = UnitsInfo.size();
	for(i=0; i<n; i++)
	{
		if (UnitsInfo[i].Zigbee)
		{
			if (verbose) printf("Do not ping unit %d Zigbee alarm\n", UnitsInfo[i].UnitNum);
		}
		else
		{
			if (usenmap)
				Nmap("Alarm", UnitsInfo[i].ZbIp);
			else
				Ping("Alarm", UnitsInfo[i].ZbIp); 
		}
		/* Only ping panel when required and possible */
		if (pflag && strlen(UnitsInfo[i].PnIp) && 0 != strcmp(UnitsInfo[i].PnIp, "0.0.0.0"))
		{
			Ping("Panel", UnitsInfo[i].PnIp); 
		}
	}
	return n;
}

int NetReport::Check(IpNeigh * ipl, 
		     int pflag)			//!< Include panels in report
{
	int i, n;
	char unum[32];
	IpStateType ips1, ips2;

	UnitsReport.clear();
	
	n = UnitsInfo.size();
	for(i=0; i<n; i++)
	{
		// Status of Zigbee gateway
		UnitsInfo[i].ZbState = ipl->GetState(UnitsInfo[i].ZbIp);
		if (pflag)
		{
			// Status of control panel, skip empty IP addresses
			if (strlen(UnitsInfo[i].PnIp) && 0 != strcmp(UnitsInfo[i].PnIp, "0.0.0.0"))
			{
				UnitsInfo[i].PnState = ipl->GetState(UnitsInfo[i].PnIp);
			}
			else
			{
				UnitsInfo[i].PnState = UNKNOWN;
			}
		}
	}
	return n;
}

int NetReport::ReCheck()
{
	int i, n;
	char unum[32];
	IpStateType ips1, ips2;

	UnitsReport.clear();
	
	n = UnitsInfo.size();
	for(i=0; i<n; i++)
	{
		// Status of Zigbee gateway
		ips1 = UnitsInfo[i].ZbState;
		if (ips1 != REACHABLE && ips1 != STALE)
		{
			if (verbose) printf("*** Recheck stand %d alarm (%s) ***\n",UnitsInfo[i].ZbIp, UnitsInfo[i].ZbIp);
			Ping("Alarm", UnitsInfo[i].ZbIp);
		}
	}
	
	return 0;
}

int NetReport::Report(int iflag, 		//!< Show IP address
		     int pflag)			//!< Include panels in report
{
	int i, n;
	char unum[32];
	int ips1, ips2;

	UnitsReport.clear();
	
	n = UnitsInfo.size();
	for(i=0; i<n; i++)
	{
		// Status of Zigbee gateway
		ips1 = UnitsInfo[i].ZbPing;
		if (ips1 <= 0)
		{
			sprintf(unum, "Stand %d (", UnitsInfo[i].UnitNum);
			UnitsReport.append(unum);
			UnitsReport.append(UnitsInfo[i].UnitName);
			UnitsReport.append(") Alarm ");
			if (iflag)
			{
				UnitsReport.append("(");
				UnitsReport.append(UnitsInfo[i].ZbIp);
				UnitsReport.append(") ");
			}
			UnitsReport.append("offline\r\n");
			if (verbose)
			{
				printf("*** Stand %d alarm offline ***\n", UnitsInfo[i].UnitNum);
				Nmap("Alarm", UnitsInfo[i].ZbIp);
			}
		}
		if (pflag)
		{
			// Status of control panel, skip empty IP addresses
			if (strlen(UnitsInfo[i].PnIp) && 0 != strcmp(UnitsInfo[i].PnIp, "0.0.0.0"))
			{
				ips2 = UnitsInfo[i].PnPing;
				if (ips2 <= 0)
				{
					sprintf(unum, "Stand %d (", UnitsInfo[i].UnitNum);
					UnitsReport.append(unum);
					UnitsReport.append(UnitsInfo[i].UnitName);
					UnitsReport.append(") Panel ");
					if (iflag)
					{
						UnitsReport.append("(");
						UnitsReport.append(UnitsInfo[i].PnIp);
						UnitsReport.append(") ");
					}
					UnitsReport.append("offline\r\n");
					if (verbose)
					{
						printf("*** Stand %d panel offline ***\n", UnitsInfo[i].UnitNum);
						Ping("Panel", UnitsInfo[i].ZbIp);
					}
				}
			}
		}
	}
	return n;
}

int NetReport::Report(IpNeigh * ipl, 
		     int iflag, 		//!< Show IP address
		     int pflag)			//!< Include panels in report
{
	int i, n;
	char unum[32];
	IpStateType ips1, ips2;

	UnitsReport.clear();
	
	n = UnitsInfo.size();
	for(i=0; i<n; i++)
	{
		// Status of Zigbee gateway
		ips1 = UnitsInfo[i].ZbState;
		if (ips1 != REACHABLE && ips1 != STALE)
		{
			sprintf(unum, "Stand %d (", UnitsInfo[i].UnitNum);
			UnitsReport.append(unum);
			UnitsReport.append(UnitsInfo[i].UnitName);
			UnitsReport.append(") Alarm ");
			if (iflag)
			{
				UnitsReport.append("(");
				UnitsReport.append(UnitsInfo[i].ZbIp);
				UnitsReport.append(") ");
			}
			UnitsReport.append(ipl->GetStateStr(ips1));
			UnitsReport.append("\n");
			if (verbose)
			{
				printf("*** Stand %d alarm offline ***\n", UnitsInfo[i].UnitNum);
				Nmap("Alarm", UnitsInfo[i].ZbIp);
			}
		}
		if (pflag)
		{
			// Status of control panel, skip empty IP addresses
			if (strlen(UnitsInfo[i].PnIp) && 0 != strcmp(UnitsInfo[i].PnIp, "0.0.0.0"))
			{
				ips2 = UnitsInfo[i].PnState;
				if (ips2 != REACHABLE && ips2 != STALE)
				{
					sprintf(unum, "Stand %d (", UnitsInfo[i].UnitNum);
					UnitsReport.append(unum);
					UnitsReport.append(UnitsInfo[i].UnitName);
					UnitsReport.append(") Panel ");
					if (iflag)
					{
						UnitsReport.append("(");
						UnitsReport.append(UnitsInfo[i].PnIp);
						UnitsReport.append(") ");
					}
					UnitsReport.append(ipl->GetStateStr(ips2));
					UnitsReport.append("\n");
					if (verbose)
					{
						printf("*** Stand %d panel offline ***\n", UnitsInfo[i].UnitNum);
						Ping("Panel", UnitsInfo[i].ZbIp);
					}
				}
			}
		}
	}
	return n;
}

const char * NetReport::Get()
{
	return UnitsReport.c_str();
}

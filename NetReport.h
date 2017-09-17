#ifndef NETREPORT_H
#define NETREPORT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <popt.h>
#include <libgen.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <libpq-fe.h>

#include <vector>

#include "IpNeigh.h"

using namespace std;

class UnitInfoRec
{
public:
	UnitInfoRec();
	~UnitInfoRec();
	
	int UnitNum;
	bool Zigbee;
	char UnitName[101];
	char Resdnt[101];
	char ZbIp[32];
	char PnIp[32];
	IpStateType ZbState;
	IpStateType PnState;
	int ZbPing;
	int PnPing;
};	

class NetReport
{
public:
	NetReport();
	~NetReport();

	int ReadDb(int zigbee);
	int ReadDbAll();
	int ReadDbNew();
	int List();
	int PingIp(const char * descr, char *Ip);
	void Ping(const char * descr, char *Ip);
	void Nmap(const char * descr, char *Ip);
	int CheckIp(int pflag);
	int ReCheckIp();
	int CheckAll(int usenmap, int pflag);
	int Check(IpNeigh * ipl, int pflag);
	int ReCheck();
	int Report(int iflag, int pflag);
	int Report(IpNeigh * ipl, int iflag, int pflag);
	const char * Get();
private:
	vector <UnitInfoRec> UnitsInfo;
	string UnitsReport;
	UnitInfoRec UnitInfo;
	PGconn * dbConn;
};

#endif

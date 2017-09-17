#include <stdio.h>
#include <libgen.h>

#include <signal.h>
#include <popt.h>

#include "IpNeigh.h"
#include "NetReport.h"

int verbose = 0;
int zigbee = 0;
int pingit = 0;
int showip = 0;
int nmapit = 0;
int showpanl = 0;
char * recpnt = NULL;

void disp_usage(char * argvst);

int UsePing();
int UseIpNeigh();

int gSendMail(char * ema, char * msg);

/*! \struct optionsTable Command line parsing data structure */
struct poptOption optionsTable[] =
{
	{"email", 	'Z', POPT_ARG_STRING, 	&recpnt, 0, "Email recipient",  "<string>"},
	{"ip",		'i', POPT_ARG_NONE, 	&showip, 0, "Show IP addresses", NULL},
	{"ping",	'p', POPT_ARG_NONE, 	&pingit, 0, "Ping all IP addresses", NULL},
	{"zigbee",	'z', POPT_ARG_NONE, 	&zigbee, 0, "Include zigbee alarms", NULL},
	{"nmap",	'p', POPT_ARG_NONE, 	&nmapit, 0, "Use nmap for alarm IP addresses", NULL},
	{"panel",	'q', POPT_ARG_NONE,	&showpanl, 0, "Include control panels in report", NULL},
	{"verbose",	'v', POPT_ARG_NONE, 	&verbose, 0, "Trace output", NULL},
	POPT_AUTOHELP
	{NULL,0,0,NULL,0}
};

void sighandle(int signum);

int main(int argc, 
         char **argv) 
{
	int rc;
	poptContext optcon;        /* Context for parsing command line options */
	
	signal(SIGINT, sighandle);
	signal(SIGQUIT, sighandle);
	signal(SIGPIPE, sighandle);

	optcon = poptGetContext(argv[0], argc, (const char **)argv, optionsTable, 0);
	rc = poptGetNextOpt(optcon);
	if (rc < -1)
	{
		fprintf(stderr, "%s: %s - %s\n", basename(argv[0]), poptBadOption(optcon,0),
			poptStrerror(rc));
		poptPrintUsage(optcon, stderr, 0);
		return -1;
	}
	poptFreeContext(optcon);
	
	if (nmapit)
		rc = UseIpNeigh();
	else
		rc = UsePing();

	return 0;
} /* main */

int UsePing()
{
	NetReport * nr;
	char * rept;
	char * mtok;

	try
	{
		nr = new NetReport;

		// Read database
		nr->ReadDb(zigbee);
		nr->CheckIp(showpanl);
		nr->ReCheckIp();
		nr->Report(showip, showpanl);
		
		rept = (char *) nr->Get();
		
		if (recpnt)
		{
			// Email report
			mtok = strtok(recpnt, ",");
			while (mtok)
			{
				gSendMail(mtok, rept);
				mtok = strtok(NULL, ",");
			}
		}
		else
		{
			// Display report
			printf("*** REPORT ***\n%s\n*** REPORT ***\n", rept);
		}
	}
	catch (...)
	{
		printf("Error caught\n");
	}
	return 0;
}

int UseIpNeigh()
{
	FILE * ipneighf;
	char ipneighb[256];
	IpNeigh * ipn;
	NetReport * nr;
	char * rept;
	char * mtok;

	try
	{
		ipn = new IpNeigh;

		nr = new NetReport;

		// Read database
		nr->ReadDb(zigbee);

		//? nr->List();
		nr->CheckAll(nmapit, showpanl);

		// Run command 
		ipneighf = popen("/sbin/ip neigh", "r");
		if (! ipneighf)
		{
			printf("Could not do 'ip neigh' command\n");
			return -1;
		}

		// Read output line by line
		fgets(ipneighb, 255, ipneighf);
		while (! feof(ipneighf))
		{
			if (verbose) printf("Read : %s", ipneighb);
			// Process information
			ipn->Add(ipneighb);
			// Next line
			fgets(ipneighb, 255, ipneighf);
		}

		// Close pipe
		pclose(ipneighf);

		nr->Check(ipn, showpanl);
		nr->Report(ipn, showip, showpanl);
		
		rept = (char *) nr->Get();
		
		if (recpnt)
		{
			// Email report
			mtok = strtok(recpnt, ",");
			while (mtok)
			{
				gSendMail(mtok, rept);
				mtok = strtok(NULL, ",");
			}
		}
		else
		{
			// Display report
			printf("*** REPORT ***\n%s\n*** REPORT ***\n", rept);
		}
		
		//? delete nr;
	}
	catch (...)
	{
		printf("Error caught\n");
	}
	return 0;
}

int gSendMail(char * ema, char * msg)
{
	int rc = 0;
	FILE * mailq;
	struct tm * dtm;
	time_t ts;
	char mailp[256];
	 
	ts = time(NULL);
	dtm = (struct tm *)localtime(&ts);
	
	if (verbose) printf("Send mail to %s\n", ema);
	
	sprintf(mailp, "/usr/bin/esmtp %s", ema);
	
	mailq = popen(mailp, "w");
	if (mailq == NULL)
	{
		printf("Could not open email");
		return -1;
	}
	
	fprintf(mailq, "Subject: MSE daily network report\n");
	fprintf(mailq, "Reply-to: jcoetzer@gmail.com\n");
	fprintf(mailq, "To: %s\n", ema);
	fprintf(mailq, "Content-type: text/plain\n\n");
	
	fprintf(mailq, "This report was generated on %04d-%02d-%02d %02d:%02d:%02d\n\n",
		 dtm->tm_year+1900, dtm->tm_mon+1, dtm->tm_mday, dtm->tm_hour, dtm->tm_min, dtm->tm_sec);
	fprintf(mailq, "%s\n", msg);
	fprintf(mailq, "End\n");
	
	if (verbose) printf("Close mail\n");

	pclose(mailq);
	
	if (verbose) printf("Mail sent to %s\n", ema);
	
	return rc;
}

/*! \brief Signal handler
 *      \param  signum  signal number
 */
void sighandle(int signum)
{
	printf("\nShutting down after signal %d\n", signum);

	exit(1);
}

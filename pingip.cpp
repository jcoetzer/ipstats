#include <stdio.h>
#include <string.h>

#include "SendPing.h"

int verbose = 0;

int main(int argc, char** argv)
{
	int rc;
	char * ipa;

	if (argc < 2)
	{
		printf("Usage: ping [-v] <IP address>\n");
		return -1;
	}
	if (argc = 3 && ! strcmp(argv[1], "-v"))
	{
		verbose = 1;
		ipa = argv[2];
	}
	else
		ipa = argv[1];
	
	rc = SendPing(ipa);
	if (rc < 0)
		printf("ping technical failure (returned %d)\n", rc);
	if (rc == 0)
		printf("ping timeout\n", rc);
	else
		printf("ping success (%d usec)\n", rc);
	return rc;
}

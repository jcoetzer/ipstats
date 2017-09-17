#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
	char syscmd[512];
   
	setuid( 0 );

	if (argc > 1)
		sprintf(syscmd, "/home/johan/bin/ipstats.sh %s", argv[1]);
	else
		sprintf(syscmd, "/home/johan/bin/ipstats.sh");
	printf("%s\n", syscmd);

	system(syscmd);

	return 0;
}
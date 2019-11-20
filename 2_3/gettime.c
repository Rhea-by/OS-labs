#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
int main(void)
{
	struct timeval getSystemTime;
	char procClockTime[256];
	int infile,len;

	gettimeofday(&getSystemTime,NULL);

	infile = open("/proc/clock",O_RDONLY);
	len = read(infile,procClockTime,256);
	close(infile);

	procClockTime[len] = '\0';

printf("SystemTime is %ld %ld\nProcClockTime is %s\n",
getSystemTime.tv_sec ,
getSystemTime.tv_usec,
procClockTime);

	sleep(1);
} 

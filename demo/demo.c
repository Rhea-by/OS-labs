#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
 
int main(int argc, char *argv[])
{
	char repTypeName[16];
  	char c1, c2, ch;
  	int interval, duration;		//the gap of time and the period of time 
  	char *lineBuf;			//the buffer of line 
  	int LB_SIZE = 255; 		//the maximum length
  	FILE *thisProcFile;		//get the profile
  	struct timeval now; 
  	int iteration;			//record the interactive influence
 
	lineBuf = (char *)malloc(sizeof(char) * LB_SIZE);
	interval = 2;			//init parameter
	duration = 60;
	strcpy(repTypeName,"Standard");
	if(argc>1)       		/*the value of argc in Linux at least is 1.so make it bigger than 1,which means get over it when there is no parameter */   
	{
		sscanf(argv[1],"%c%c",&c1,&c2);
		if(c1 != '-')
		{
			fprintf(stderr,"usage:ksamp [-s][-l int dur]\n");
			exit(1);
		}
		if(c2 == 's')
		{
			strcpy(repTypeName,"Short");
		}
		if(c2 == 'l')
		{
			strcpy(repTypeName,"Long");
			interval = atoi(argv[2]);
			duration = atoi(argv[3]);
		}	
	}
	//get time
	gettimeofday(&now,NULL);
	printf("Status report %s at %s\n", repTypeName, ctime(&(now.tv_sec)));
	//correct the call of function ctime()
	//get the hostname
	thisProcFile = fopen("/etc/hostname","r");
	memset(lineBuf, 0, LB_SIZE);
	fgets(lineBuf, LB_SIZE - 1, thisProcFile);
	printf("Machine host name: %s\n",lineBuf);
	fclose(thisProcFile);
	//get the information of version
	thisProcFile = fopen("/proc/version","r");
	memset(lineBuf, 0, LB_SIZE);
	fgets(lineBuf, LB_SIZE - 1, thisProcFile);
	printf("Machine host name: %s\n",lineBuf);
	fclose(thisProcFile);
	//get the information of CPU
	thisProcFile = fopen("/proc/cpuinfo","r");
	memset(lineBuf, 0, LB_SIZE);
	fgets(lineBuf, LB_SIZE - 1, thisProcFile);
	printf("The CPU: %s\n",lineBuf);
	fclose(thisProcFile);
	//get the current time
	thisProcFile = fopen("/proc/uptime","r");
	memset(lineBuf, 0, LB_SIZE);
	fgets(lineBuf, LB_SIZE - 1, thisProcFile);
	printf("The Runing Time: %s\n",lineBuf);
	fclose(thisProcFile);
	//get the information of mem
	printf("The Meminfo: ");
	thisProcFile = fopen("/proc/meminfo", "r");
	while(!feof(thisProcFile))
	{
		putchar(fgetc(thisProcFile));
	}
	fclose(thisProcFile);
	//get the current status
	printf("The Status: ");
	thisProcFile = fopen("/proc/stat", "r");
	while(!feof(thisProcFile))
	{
		putchar(fgetc(thisProcFile));
	}
	fclose(thisProcFile);
	iteration = 0;
	while(iteration < duration)
	{
		sleep(interval);
		thisProcFile = fopen("/proc/loadavg" ,"r");
		while(!feof(thisProcFile))
		{
			putchar(fgetc(thisProcFile));
		}
		fclose(thisProcFile);
		iteration += interval;
	}
	return 0;
}
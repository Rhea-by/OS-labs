/**************part3.c***************/
//part3
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
static void c1_sighandle(int s);
static void c2_sighandle(int s);
static void p_sighandle(int s);
static long p_realt_secs = 0,c1_realt_secs = 0,c2_realt_secs = 0;
static long p_virtt_secs = 0,c1_virtt_secs = 0,c2_virtt_secs = 0;
static long p_proft_secs = 0,c1_proft_secs = 0,c2_proft_secs = 0;
static struct itimerval p_realt,c1_realt,c2_realt;
static struct itimerval p_virtt,c1_virtt,c2_virtt;
static struct itimerval p_proft,c1_proft,c2_proft;
static struct itimerval ini_value;

int fibonacci(int n);
static void c1_sighandle(int s);
static void c2_sighandle(int s);
static void p_sighandle(int s);


int main(){
 int fib = 0;
 int pid1,pid2;
 int status;
 long moresec,moremsec,t1,t2;
 pid1 = fork();
 if (pid1 == 0){//c1
 		//set c1 signal handle
		signal(SIGALRM,c1_sighandle);
		signal(SIGVTALRM,c1_sighandle);
		signal(SIGPROF,c1_sighandle);

		ini_value.it_interval.tv_sec = 10;
 		ini_value.it_interval.tv_usec = 0;
 		ini_value.it_value.tv_sec = 10;
 		ini_value.it_value.tv_usec = 0;

		//set c1 timer
 		setitimer(ITIMER_REAL,&ini_value,NULL);
 		setitimer(ITIMER_VIRTUAL,&ini_value,NULL);
 		setitimer(ITIMER_PROF,&ini_value,NULL);

 		fib = fibonacci(20);
 		//get timer of c1 and print

 		getitimer(ITIMER_REAL,&c1_realt);
 		getitimer(ITIMER_VIRTUAL,&c1_virtt);
		getitimer(ITIMER_PROF,&c1_proft);

 		printf("\n");
		moresec = 10 - c1_realt.it_value.tv_sec;
		moremsec = (1000000 - c1_realt.it_value.tv_usec)/1000;
printf("c1fib(20)=%d\nrealtime=%ldsec,%ldmsec\n",fib,c1_realt_secs+moresec,moremsec);

		moresec = 10 - c1_proft.it_value.tv_sec;
		moremsec = (1000000 - c1_proft.it_value.tv_usec)/1000;
		printf("cputime = %ld sec, %ld msec\n",c1_proft_secs+moresec,moremsec);

		moresec = 10 - c1_virtt.it_value.tv_sec;
		moremsec = (1000000 - c1_virtt.it_value.tv_usec)/1000;
		printf("usertime = %ld sec, %ld msec\n",c1_virtt_secs+moresec,moremsec);

		 t1=(10-c1_proft.it_value.tv_sec)*1000+(1000000-c1_proft.it_value.tv_usec)/1000 + c1_proft_secs*10000;
	  	 t2=(10-c1_virtt.it_value.tv_sec)*1000+(1000000-c1_virtt.it_value.tv_usec)/1000 + c1_virtt_secs*10000;
		moresec = (t1 - t2)/1000;
		moremsec = (t1 - t2) % 1000;
		printf("kerneltime = %ld sec, %ld msec\n",moresec,moremsec);
		fflush(stdout);
 		exit(0);
 	      }//end c1
 else{
 	pid2 = fork();
 	if (pid2 == 0){//c2
 			//set c2 signal handle
 			signal(SIGALRM,c2_sighandle);
			signal(SIGVTALRM,c2_sighandle);
			signal(SIGPROF,c2_sighandle);

			ini_value.it_interval.tv_sec = 10;
 			ini_value.it_interval.tv_usec = 0;
			ini_value.it_value.tv_sec =10;
 			ini_value.it_value.tv_usec = 0;

			//set c2 timer
			 setitimer(ITIMER_REAL,&ini_value,NULL);
			 setitimer(ITIMER_VIRTUAL,&ini_value,NULL);
			 setitimer(ITIMER_PROF,&ini_value,NULL);

 			fib = fibonacci(30);
			 //get timer of c2 and print
			 getitimer(ITIMER_PROF,&c2_proft);
			 getitimer(ITIMER_REAL,&c2_realt);
			 getitimer(ITIMER_VIRTUAL,&c2_virtt);

			printf("\n");
			moresec = 10 - c2_realt.it_value.tv_sec;
			moremsec = (1000000 - c2_realt.it_value.tv_usec)/1000;
			 printf("c2fib(30)=%d\nrealtime=%ldsec,%ldmsec\n",fib,c2_realt_secs+moresec,moremsec);
			moresec = 10 - c2_proft.it_value.tv_sec;
			moremsec = (1000000 - c2_proft.it_value.tv_usec)/1000;
			printf("cputime=%ldsec,%ldmsec\n",c2_proft_secs+moresec,moremsec);
			moresec = 10 - c2_virtt.it_value.tv_sec;
			moremsec = (1000000 - c2_virtt.it_value.tv_usec)/1000;
			printf("usertime=%ldsec,%ldmsec\n",c2_virtt_secs+moresec,moremsec);

			 t1=(10-c2_proft.it_value.tv_sec)*1000+(1000000-c2_proft.it_value.tv_usec)/1000 + c2_proft_secs*10000;
			 t2=(10-c2_virtt.it_value.tv_sec)*1000+(1000000-c2_virtt.it_value.tv_usec)/1000 + c2_virtt_secs*10000;
			moresec = (t1 - t2)/1000;
			moremsec = (t1 - t2) % 1000;
			printf("kerneltime = %ld sec, %ld msec\n",moresec,moremsec);
 			fflush(stdout);
 			exit(0);
 			}//endc2
	}
//parent
 //setparent signal handle
 signal(SIGALRM,p_sighandle);
 signal(SIGVTALRM,p_sighandle);
 signal(SIGPROF,p_sighandle);

 ini_value.it_interval.tv_sec = 10;
 ini_value.it_interval.tv_usec = 0;
 ini_value.it_value.tv_sec = 10;
 ini_value.it_value.tv_usec = 0;

//set parent timer
 setitimer(ITIMER_REAL,&ini_value,NULL);
 setitimer(ITIMER_VIRTUAL,&ini_value,NULL);
 setitimer(ITIMER_PROF,&ini_value,NULL);

 fib = fibonacci(36);

 getitimer(ITIMER_PROF,&p_proft);
 getitimer(ITIMER_REAL,&p_realt);
 getitimer(ITIMER_VIRTUAL,&p_virtt);

 printf("\n");
 moresec = 10 - p_realt.it_value.tv_sec;
 moremsec = (1000000 - p_realt.it_value.tv_usec)/1000;
 printf("pfib(36)=%d\nrealtime=%ldsec,%ldmsec\n",fib,p_realt_secs+moresec,moremsec);

 moresec = 10 - p_proft.it_value.tv_sec;
 moremsec = (1000000 - p_proft.it_value.tv_usec)/1000;
 printf("cputime = %ld sec, %ld msec\n",p_proft_secs+moresec,moremsec);

 moresec = 10 - p_virtt.it_value.tv_sec;
 moremsec = (1000000 - p_virtt.it_value.tv_usec)/1000;
 printf("usertime = %ld sec, %ld msec\n",p_virtt_secs+moresec,moremsec);

 t1= (10 - p_proft.it_value.tv_sec)*1000 + (1000000 - p_proft.it_value.tv_usec)/1000 + p_proft_secs*10000;
 t2 = (10 - p_virtt.it_value.tv_sec)*1000 + (1000000 - p_virtt.it_value.tv_usec)/1000 + p_virtt_secs*10000;
 moresec = (t1 - t2)/1000;
 moremsec = (t1 - t2) % 1000;
 printf("kerneltime = %ld sec, %ld msec\n",moresec,moremsec);

 fflush(stdout);
 //wait c1,c2 terminal
 wait(&status);
 wait(&status);
 return 0;
 }//end main

 int fibonacci(int n)
 {
   if( n == 0 ) return 0;
    else if( n == 1 || n == 2) return 1;
    else return(fibonacci(n-1)+fibonacci(n-2) );
 }

static void c1_sighandle(int s)
{
	switch(s){
		case SIGALRM:c1_realt_secs+=10;break;
	        case SIGVTALRM:c1_virtt_secs+=10;break;
	        case SIGPROF:c1_proft_secs+=10;break;
		default :break;
		}
}

static void c2_sighandle(int s)
{
	switch(s){
		case SIGALRM:c2_realt_secs+=10;break;
	        case SIGVTALRM:c2_virtt_secs+=10;break;
	        case SIGPROF:c2_proft_secs+=10;break;
		default :break;
		}
}

static void p_sighandle(int s)
{
	switch(s){
		case SIGALRM:p_realt_secs+=10;break;
	        case SIGVTALRM:p_virtt_secs+=10;break;
	        case SIGPROF:p_proft_secs+=10;break;
		default :break;
		}
}

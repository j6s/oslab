#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

struct timespec tspc;
int count = 0;
int tm = 0;

void start(){
	clock_gettime(CLOCK_REALTIME,&tspc);
	tm = tspc.tv_sec;
	printf("yo, start tha clock\n");
}

void stop(){
	clock_gettime(CLOCK_REALTIME,&tspc);
	int t = tspc.tv_sec - tm;
	tm = tspc.tv_sec;
        printf("yo, stop tha clock: %ds\n",t);
}

void myhandler(int signal){

	switch(signal){
		case SIGUSR1:
			start();
		break;
		case SIGUSR2:
			stop();
		break;
		case SIGTSTP:
			printf("count: %d",count);
			if(count == 0){
				start();
				count = 1;
			} else {
				stop();
				count = 0;
			}
		break;
		default:
			printf("yo, signal %d is not known\n",signal);
		break;
	}
}


int main(){
	printf("pid: %d\n",getpid());
	signal(SIGTSTP, myhandler);
	signal(SIGUSR1, myhandler);
	signal(SIGUSR2, myhandler);
	while(1);
}

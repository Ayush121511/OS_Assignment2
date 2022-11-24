#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include  <string.h>
#include <sys/wait.h>
#include <pthread.h>

enum {NS_PER_SECOND = 1000000000 };

void sigsegv_handler(int sig)
{
	printf("SIGSEGV recieved\n");
	exit(1);
}

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td){
	td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
 	td->tv_sec = t2.tv_sec - t1.tv_sec;
	if(td->tv_sec >0 && td->tv_nsec <0)
	{
		td->tv_nsec += NS_PER_SECOND;
		td->tv_sec--;
	}
	else if (td->tv_sec<0 && td->tv_nsec >0){
		td->tv_nsec -= NS_PER_SECOND;
		td->tv_sec++;
	}
}

int main (int argc, char** argv){
	int status;
	struct timespec start,finish,delta;
	for(int i=0;i<10;i++){
		clock_gettime(CLOCK_REALTIME,&start);
		int pid1 = fork();
		if(pid1==0){
			struct sched_param p1;
			p1.sched_priority = 40 + 2*i ;
			sched_setscheduler(pid1,SCHED_RR,&p1);
			system("chmod u+x bash1.sh");
			execl("bash1.sh","sh",NULL);
		}
		else{
//			wait(&status);
//			clock_gettime(CLOCK_REALTIME, &finish);
//			sub_timespec(start, finish, &delta);
//			printf("P1 %d.%.9ld\n",(int)delta.tv_sec, delta.tv_nsec);
			int pid2 = fork();
			if(pid2==0){
				struct sched_param p2;
				p2.sched_priority = 0;
				sched_setscheduler(pid2,SCHED_OTHER,&p2);
				system("chmod u+x bash2.sh");
				execl("bash2.sh","sh",NULL);
			}
			else{
			//	wait(&status);
//				clock_gettime(CLOCK_REALTIME, &finish);
			//	sub_timespec(start, finish, &delta);
			//	printf("P2 %d.%.9ld\n",(int)delta.tv_sec, delta.tv_nsec);
				int pid3 = fork();
				int i = 1;
				if(pid3==0){
					struct sched_param p3;
					p3.sched_priority = 40 +2*i ;
					sched_setscheduler(pid2,SCHED_FIFO,&p3);
					system("chmod u+x bash3.sh");
					execl("bash3.sh","sh",NULL);
				}
				else{
					int nProg=1;
					int pid;;
					while(nProg<=3){
						pid = waitpid(-1,NULL,WNOHANG);
						clock_gettime(CLOCK_REALTIME, &finish);
						if(pid == pid1){
							sub_timespec(start, finish, &delta);
							FILE* ptr;
		        				ptr = fopen("q1B.txt","a");
							fprintf(ptr,"rr: %d.%.9ld\n",(int)delta.tv_sec, delta.tv_nsec);
							fclose(ptr);
							nProg++;
       						}
						else if(pid == pid2){
							sub_timespec(start, finish, &delta);
							FILE* ptr;
		        				ptr = fopen("q1B.txt","a");
							fprintf(ptr,"other: %d.%.9ld\n",(int)delta.tv_sec, delta.tv_nsec);
       							fclose(ptr);
							nProg++;
						}
						else if(pid == pid3){
							sub_timespec(start, finish, &delta);
							FILE* ptr;
		        				ptr = fopen("q1B.txt","a");
							fprintf(ptr,"fifo: %d.%.9ld\n",(int)delta.tv_sec, delta.tv_nsec);
							fclose(ptr);
							nProg++;
						}
					}
				}
			}
		}
	}
}

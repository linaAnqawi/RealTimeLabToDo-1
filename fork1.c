#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
	}

	int main()
	{
pid_t p;
int s ; 
int myInts[100];//our array for 100 int 
int total[2];
int i,j, stat;
pid_t pid[2]; 
int sum1;
int sum2;
int sumation;
int size=sizeof(myInts)/sizeof(myInts[0]);
struct timeval tv;
gettimeofday(&tv,NULL);
long time_in_micros1;
long time_in_micros = getMicrotime();
printf("Time before fork Microseconds: %ld\n",time_in_micros);
	for(i=0;i<size;i++){
			myInts[i]=rand()%5+1;
			}
	for (i=0; i<2; i++) { 
		if ((pid[i] = fork()) == 0) 
			{ 
			sleep(5); 
			for(j=0;j<49;j++){
			sum1=sum1+myInts[j];
			}
			for(j=50;j<99;j++){
			sum2=sum2+myInts[j];
			}
			if(i==0){
			exit(sum1);
			}else{
			exit(sum2);
			}
			}
	}
	for (i=0; i<2; i++){ 
	pid_t cpid = waitpid(pid[i], &stat, 0); 
        total[i]=WEXITSTATUS(stat);
	printf("Child %d terminated with suamtion: %d\n", 
	cpid, WEXITSTATUS(stat)); 
			} 

	if (pid < 0) { /* error occurred */
	fprintf(stderr, "Fork Failed");
	exit(0);
	}
	else if (pid != 0){
	time_in_micros1 = getMicrotime();
	printf("Time after fork Microseconds: %ld\n",time_in_micros1);
	time_in_micros1 = getMicrotime()-time_in_micros;
	printf("PROCESS TIME: %ld\n",time_in_micros1);	
	printf ("Parent! pid is %d\n",getpid());
	sumation=total[0]+total[1];
	printf ("total sumation of array %d\n",sumation);
	exit(0);
	}
}













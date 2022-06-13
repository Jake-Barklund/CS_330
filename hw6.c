#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/wait.h>

void *thread(void *arg){
	int currentThread = (int)arg;
	
	int cnt = 0;

	for(int i = 0;i < 1000000000;i++){
		if (i % 10000000 == 0){
			printf("Thread:%d\t:%d\n",currentThread,cnt);
			cnt++;
		}
	}
	return NULL;
}

void runProcesses(int processes){
	pid_t child;

	int cnt = 0;

	for (int j = 0; j < processes;j++){
		child = fork();

		if (child == 0){
			int pid = getpid();
			for(int i = 0;i < 1000000000;i++){
				if (i % 10000000 == 0){
					printf("Process:%d\t:%d\n",pid,cnt);
					cnt++;
				}
			}
			exit(0);
			return;
		}
	
	}
	while(wait(NULL) != -1);
	
	return;
}

int main(int argc, char* argv[]){
	struct timeval startTime;
	struct timeval endTime;

	int numThreads = atoi(argv[1]);
	int numProcesses = atoi(argv[2]);

	pthread_t *x = NULL;
	x = malloc(sizeof(pthread_t) * numThreads);

	//Setting nice to highest level for first execution of threads
	int niceValHigh = nice(0);	

	gettimeofday(&startTime,NULL);

	//Executing threads code
	for (int i = 0; i < numThreads;i++){
		pthread_create((x+i),NULL,thread,(void*)+i);
	}

	for (int i = 0; i < numThreads;i++){
		pthread_join(*(x+i),NULL);
	}

	//Getting time lapsed for threads code
	gettimeofday(&endTime,NULL);

	int elapsedTimeThreadsHigh = endTime.tv_sec - startTime.tv_sec;

	free(x);

	//Process code
	gettimeofday(&startTime,NULL);

	runProcesses(numProcesses);

	gettimeofday(&endTime,NULL);

	int elapsedTimeProcessHigh = endTime.tv_sec - startTime.tv_sec;

	//Setting nice to the lowest level for second executions of threads
	int niceValLow = nice(19);
	
	pthread_t *y = NULL;
	y = malloc(sizeof(pthread_t) * numThreads);

	gettimeofday(&startTime,NULL);

	//Executing threads low-prio code
	for (int i = 0; i < numThreads;i++){
		pthread_create((y+i),NULL,thread,(void*)+i);
	}

	for (int i = 0; i < numThreads;i++){
		pthread_join(*(y+i),NULL);
	}

	free(y);

	//Getting time elapsed for threads code with low-prio
	gettimeofday(&endTime,NULL);
	
	int elapsedTimeThreadsLow = endTime.tv_sec - startTime.tv_sec;

	//Executing process with low prio
	gettimeofday(&startTime,NULL);
	
	runProcesses(numProcesses);

	gettimeofday(&endTime,NULL);

	int elapsedTimeProcessLow = endTime.tv_sec - startTime.tv_sec;
	
	//Printing results
	printf("%d Threads:\n\tTime with nice(%d): %ds\n\tTime with nice(%d): %ds\n",numThreads,niceValHigh,elapsedTimeThreadsHigh,niceValLow,elapsedTimeThreadsLow);
	printf("%d Processes:\n\tTime with nice(%d): %ds\n\tTime with nice(%d): %ds\n",numProcesses,niceValHigh,elapsedTimeProcessHigh,niceValLow,elapsedTimeProcessLow);

	return 0;
}
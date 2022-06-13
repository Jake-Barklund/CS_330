#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#include <pthread.h>

#define MAX_FILE_SIZE 16384

char file[MAX_FILE_SIZE];
char inputChar = ' ';
int charCnt = 0;
int fileLength = 0;
int fileOffset = 0;
pthread_mutex_t lock;

void counter(int start, int end) {

     pthread_mutex_lock(&lock);

     for (int i = start; i < end; i++){
      if(file[i] != inputChar){continue;}

      charCnt++;
     }

     pthread_mutex_unlock(&lock);

     return;
}


void *thread(void *arg) {

     int currentThread  = (int)arg;

     counter(fileOffset*currentThread,fileOffset*(currentThread+1));

     return NULL;
}

int main(int argc, char *argv[]) {

     struct timeval timeS;
     struct timeval timeE;

     int numThreads = 0;
     int cnt = 0;

     FILE *inputFile;
     inputFile = fopen(argv[3],"r");

     while(!feof(inputFile) && cnt < MAX_FILE_SIZE){
      file[cnt] = fgetc(inputFile);
      cnt++;
     }

     fileLength = cnt;

     inputChar = *(argv[1]);

     pthread_t *x = NULL;

     pthread_mutex_init(&lock, NULL);

     numThreads = atoi(argv[2]);

     fileOffset = fileLength / numThreads;

     x = malloc(sizeof(pthread_t) * numThreads );

     int startTime = gettimeofday(&timeS,NULL);

     for(int i = 0; i < numThreads;i++){
      pthread_create((x+i), NULL, thread, (void*)+i);
     }

     for(int i = 0; i < numThreads;i++){
      pthread_join(*(x+i),NULL);
     }

     int endTime = gettimeofday(&timeE,NULL);

     free(x);

     pthread_mutex_destroy(&lock);

     int elapse = (timeE.tv_usec - timeS.tv_usec);

     printf("\nTime elapsed:\t%d us\n",elapse);
     printf("Threads used: %d\n",numThreads);
     printf("Given Char: %c\tAmount found: %d\n", inputChar,charCnt);

     return EXIT_SUCCESS;
}

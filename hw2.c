#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc, char* argv[]){

 struct timeval timeS;
 struct timeval timeE;
 pid_t child;

 int y = gettimeofday(&timeE,NULL);

 child = fork();
 if (child == 0){
  execve(argv[1],NULL,NULL);
 }
 while(wait(NULL) != -1); 

 int x = gettimeofday(&timeS,NULL);

 printf("Done!\n");

 int elapse = timeS.tv_usec - timeE.tv_usec;

 printf("Time elapsed:\t%d us\nStart time:\t%ld us\nEnd time:\t%ld us\n",elapse,timeS.tv_usec,timeE.tv_usec);


 return 0;
}
#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc, char* argv[]){

 struct timeval timeS;
 struct timeval timeE;
 pid_t child;

 printf("Stating time for mulitple CPUs\n");

 int y = gettimeofday(&timeE,NULL);

 child = fork();
 if (child == 0){
  execve("/home/undergrad/jacobsma/www/CS330/HW4/multiCPU",NULL,NULL);
  return 0;
 }
 wait(NULL);

 int x = gettimeofday(&timeS,NULL);

 printf("\nDone!\n");

 int elapse = (timeS.tv_usec - timeE.tv_usec);

 printf("\nTime elapsed:\t%d us\nStart time:\t%ld us\nEnd time:\t%ld us\n",elapse,timeS.tv_usec,timeE.tv_usec);


 //Second execve


 struct timeval timeS2;
 struct timeval timeE2;
 pid_t child2;

 printf("\nStarting time for single CPU\n");

 int y2 = gettimeofday(&timeE2,NULL);

 child2 = fork();
 if (child2 == 0){
  execve("/home/undergrad/jacobsma/www/CS330/HW4/singleCPU",NULL,NULL);
  return 0;
 }
 wait(NULL);

 int x2 = gettimeofday(&timeS2,NULL);

 printf("\nDone!\n");

 int elapse2 = (timeS2.tv_usec - timeE2.tv_usec);

 printf("\nTime elapsed:\t%d us\nStart time:\t%ld us\nEnd time:\t%ld us\n",elapse2,timeS2.tv_usec,timeE2.tv_usec);

 return 0;
}
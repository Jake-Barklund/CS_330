//Written by Jake Barklund

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

struct timeval timer();
int printtime(int totalelapsed);
//Function that will get the time, used for both start and end timers as they would be the same code
struct timeval timer(){
    struct timeval time;
    gettimeofday(&time, NULL);
    return time;
}
//Function that will take in total time in microseconds then print the value
int printtime(int totalelapsed){
    printf("%d microseconds to print", totalelapsed);
}
//Main function that will call the starting time, then perform a function of sleeping, then get the end time.
//It will print out the end time in microseconds using the prior functions
int main(){
	struct timeval starttime, endtime;
	int totalelapsed;

	starttime = timer();

	sleep(3);

    endtime = timer();
    totalelapsed = endtime.tv_usec - starttime.tv_usec;
    printtime(totalelapsed);

    return 0;
}

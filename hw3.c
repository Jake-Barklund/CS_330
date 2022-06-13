#include<sys/wait.h>
#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<string>

using namespace std;

int main(void){

 string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
 pid_t child;

 for (int j = 0; j < 12;j++){
  for (int i = 0; i < 26;i++){
   child = fork();

   if (child == 0){
    cout << alpha[i];
    return 0;
   }
  }


  while( wait(NULL) != -1);
  cout << '\n';
 }
 return 0;
}
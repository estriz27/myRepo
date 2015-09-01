#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char* main(int argc, char*str)
{
  pid_t  pid;
  pid_t  pid2;
  int num = 0;
 
 
  if (pid = fork()){
    if(pid2 = fork()){

      while(1){

          printf("Parent: "); 
	  printf("%d\n", num);
	  num++;
      }
    }
    else{
      while(1){
          printf("Child2: %d\n ", num);
	  num++;
      }
    }
  }
 else{
   while(1){
       printf("Child1: %d\n ", num);
       num++;
     }
 }
}




 

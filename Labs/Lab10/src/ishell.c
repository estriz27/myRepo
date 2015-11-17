#include <stdio.h>
#include <stdlib.h>
#include "wrappers.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

char *args[20];
bool boolean = true;


char **tokenizer(char *string){
  int count = 1;

  char *token; 
  token = strtok(string," ");
  args[0] = token;  

  while (token != NULL){
    token = strtok(NULL, " ");
    args[count] = token;
    count ++;
  }
  args[count] = NULL;


  return args;

}


int main(int argc, char *argv[]){
  char line[200];
	int pid;
	int status; // exit status to be filled by wait

 
  

                                                                                                                                                                             
	printf("ishell> "); 
  //getline(&line, &n, stdin);
  gets(line);

  while(1){
  tokenizer(line); 
                                                                                                                                                               
  	//child process
  	if ((pid = Fork()) == 0) {

      Execvp(args[0], args); 
	    exit(0);
	   }

  	//parent process
  	else {
  	wait(&status); // note we are not catching the return value of wait!
 // 	printf("parent got termination status= %d from child\n", status);

  	printf("ishell> ");
	  gets(line);

	

  	}
  }
}


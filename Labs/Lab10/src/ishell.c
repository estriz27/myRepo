#include <stdio.h>
#include <stdlib.h>
#include "wrappers.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>



#define MAX_ARGS 20


int tokenizer(char *string, char *array[], char *d){
  int count = 1;

  char *token; 
  token = strtok(string, d);

  array[0] = token;  

  while (token != NULL && count< MAX_ARGS-1){
    token = strtok(NULL, d);
    array[count] = token;
    count ++;
  }
  array[count] = NULL;

  return count;

}

void cmd_exe(char **args){

  int pid;
  int status;

  if((pid = Fork()) == 0){
    Execvp(args[0], args);
  }

  else {
    wait(&status);
  }
}



int main(int argc, char *argv[]){
  char line[200];
  char *lines[MAX_ARGS];
  char *args[MAX_ARGS];
  int count = 0;

  printf("ishell> "); 
  gets(line);


  while(1){

  count = tokenizer(line, lines, ";");

  for (int i =0; i< count; i++){
    tokenizer(lines[i], args, " ");
    cmd_exe(args);
  }

    printf("ishell> ");
    gets(line);

    }
  }





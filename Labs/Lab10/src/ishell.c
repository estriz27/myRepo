//Elias Strizower
//CSCI 315
//Lab 10

#include <stdio.h>
#include <stdlib.h>
#include "wrappers.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>



#define MAX_ARGS 20

//Added exit functionality. If "exit" is typed into the shell, it will exit the ishell process.
int tokenizer(char *string, char *array[], char *d){
  int count = 0;

  char *token; 
  token = strtok(string, d);

  array[0] = token;  

  while (token != NULL && count< MAX_ARGS-1){
    token = strtok(NULL, d);
    count ++;
    array[count] = token;
    
  }
  array[count+1] = NULL;

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
    if (status == 0){
      printf("[ishell: program terminated successfully]\n");
    }
  }
}



int main(int argc, char *argv[]){
  char line[200];
  char *lines[MAX_ARGS];
  char *args[MAX_ARGS];
  int count = 0;
  int space = 0;


  printf("ishell> "); 
  gets(line);


  while(1){

    count = tokenizer(line, lines, ";");

    for (int i =0; i< count; i++){
      tokenizer(lines[i], args, " ");

      if(space == 1 && args[i] == NULL){
        args[0] = "ls";
        cmd_exe(args);

        space = 0;
        break;
      }

      if(args[i] == NULL){
        space ++;
      }
      if (strcmp(args[0],"exit") == 0){
        exit(0);
      }


      cmd_exe(args);
    }

    printf("ishell> ");
    gets(line);

  }
}





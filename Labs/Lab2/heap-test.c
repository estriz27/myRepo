//Elias Strizower
//CSCI 315
//Lab 2 Prelab
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



int main(int argc, char* argv[]){

  char *string = (char *) malloc(20);
  int pid;
  strcpy(string, "This is a test of heap");
  printf("The parent initially has the heap: %s\n", string);

  if ((pid = fork()) == 0){
      //child process
    
      printf("The child copied the heap of the parent: %s\n", string);
      strcpy(string, "Child changed string");
       printf("The child altered the heap: %s\n", string);

      

    }

    else {

      //parent process
      wait();
      printf("The parent is reading the heap: %s\n", string);
      strcpy(string, "The parent has altered the heap");
      printf("The parent changed the heap: %s\n", string);
      

      
    }
    
    exit(0);
    }

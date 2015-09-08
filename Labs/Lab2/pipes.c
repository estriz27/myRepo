//Elias Strizower
//CSCI315
//Lab 2 Prelab 




#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 25
#define READ_END 0 
#define WRITE_END 1

int Pipe(int pipefd[2]){
  if (pipe(pipefd) < 0){
    perror("Error creating pipe");
    exit(-1);
  }
  return(0);
}


int Read(int fd, void *buf, size_t count){
 int resultR =  read(fd, buf, count);
  if(resultR < 0){
    perror("Error reading from pipe");
    exit(-1);
  }
  else{
    return resultR;
  }
}
  
  int Write(int fd, const void *buf, size_t count){
    int resultW = write(fd, buf, count);
    if(resultW <0){
      perror("Error writing to pipe");
    }
    else{
      return resultW;
  }
  }

int main(void)
{
  char write_msg[BUFFER_SIZE] = "\nGreetings\n";
  char read_msg[BUFFER_SIZE];
  int fd[2];
  pid_t pid;
  int x = 0;
  int y = 0;
  
  /* create the pipe */
  Pipe(fd);
  
  /* fork a child process */
  pid = fork();
  
  if (pid < 0) { 
    /* error occurred */
    fprintf(stderr, "Fork Failed"); return 1;
  }
  
  if (pid > 0) { /* parent process */
    /* close the unused end of the pipe */
    close(fd[READ_END]);
  
    /* write to the pipe */
    
    while (write_msg[x] != 0){
    Write(fd[WRITE_END],(void*) &write_msg[x], 1);
    // write(fd[WRITE_END],"\n" , 1);    //test to see if writing 1 char at a time
    x++;
    }
    /* close the write end of the pipe */
    close(fd[WRITE_END]);
  }
 else { /* child process */
   /* close the unused end of the pipe */
   close(fd[WRITE_END]);
   /* read from the pipe */
   while(1){
     Read(fd[READ_END],(void*) &read_msg[y], 1);
     printf("read %c \n",read_msg[y]);
     
     if(read_msg[y] == 0){
       break;
     }
     y++;
   }
   /* close the write end of the pipe */
   close(fd[READ_END]);
 }
 
  return 0;
}

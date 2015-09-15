//Elias Strizower
//CSCI315
//Lab 2 Prelab 




#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 100
#define READ_END 0 
#define WRITE_END 1

char buffer[BUFFER_SIZE] = "";
int strlength;

int Fork(void){
  pid_t pid;
  if((pid = fork()) == -1){
    perror("Error creating child process");
    exit(-1);
  }
  else{
    return pid;
  }
}

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
      exit(-1);
    }
    else{
      return resultW;
  }
  }

int main(void)
{
 
  char read_msg[BUFFER_SIZE];
  char read_msg2[BUFFER_SIZE];
  
  int fd[2];
  int fd2[2];
  pid_t pid;

  
  /* create the pipe */
  Pipe(fd);
  Pipe(fd2);
  
  /* fork a child process */
  pid = Fork();
  
  
  if (pid > 0) { /* parent process */
    /* close the unused end of the pipe */
    close(fd[READ_END]);
    close(fd2[WRITE_END]);
  
    /* write to the pipe */
    
    while (1){
      int msglen2;
      fgets(buffer,sizeof(buffer), stdin);
      strlength = strlen(buffer)+1;
      Write(fd[WRITE_END],&strlength, sizeof(int));
      Write(fd[WRITE_END], buffer, strlength);
      //read stuff and print it
      Read(fd2[READ_END],&msglen2, sizeof(int));
      Read(fd2[READ_END], read_msg2, msglen2);
      printf("This is the final message: %s", read_msg2);
    }
 
       
  //Close the read end of the pipe
     close(fd2[READ_END]);
  /* close the write end of the pipe */
    close(fd[WRITE_END]);
  }


 else { /* child process */
   /* close the unused end of the pipe */
   close(fd[WRITE_END]);
   close(fd2[READ_END]);
   /* read from the pipe */
   while(1){
     int msglen;
     Read(fd[READ_END], &msglen, sizeof(int));
     Read(fd[READ_END], read_msg, msglen);
     printf("read_msg: %s ", read_msg);
     //catting stuff, afterward calc new strlength + 1 for the catted stuff and send to parent
     char *token;
     char tokenized[BUFFER_SIZE] = "";

     token = strtok(read_msg, " ");

     while(token!= NULL){
       strcat(tokenized, token);
       strcat(tokenized, " ");
       token = strtok(NULL, " ");
     }
     strlength = strlen(tokenized)+1;
  

     Write(fd2[WRITE_END], &strlength, sizeof(int));
     Write(fd2[WRITE_END], tokenized, strlength);
     
   }

   close(fd[READ_END]);

    /* close the write end of the pipe */
   close(fd2[WRITE_END]);
 }
   
}
 



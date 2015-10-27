#include "wrappers.h"


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
	int pipeRet = pipe(pipefd);
  if (pipeRet < 0){
    perror("Error creating pipe");
    exit(-1);
  }
  return(pipeRet);
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

  int Wait(int *waitInt){
  	int waitResult = wait(waitInt);
  	if (waitResult < 0){
  		perror("Error executing wait");
  		exit(-1);
  	} 
  	return(waitResult);
  }

  int Waitpid(pid_t pid, int *stat_loc, int options){
  	int waitpidRes = waitpid(pid, stat_loc, options);
  	if (waitpidRes < 0){
  		perror("Error executing waitpid");
  		exit(-1);
  	} 
  	return(waitpidRes);
  }

  int Open(const char *path, int log){
  	int openRet = open(path, log);
  	if(openRet < 0){
  		perror("Error executing open");
  		exit(-1);
  	}
  	return(openRet);
  }

  int Close(int fildes){
  	int closeRet = close(fildes);
  	if (closeRet <0){
  		perror("Error executing close");
  		exit(-1);
  	}
  	return(closeRet);
  }

  int Connect(int socket, const struct sockaddr *address, socklen_t addresslen){
  	int connectRet = connect(socket, address, addresslen);
  	if(connectRet < 0){
  		perror("Error connecting");
  		exit(-1);
  	}
  	return(connectRet);
  }

 int Bind(int socket, const struct sockaddr *address, socklen_t addresslen){
 	int bindRet = bind(socket, address, addresslen);
 	if(bindRet <0){
 		perror("Error binding");
 		exit(-1);
 	}
 	return(bindRet);
 }
 int Listen(int socket, int backlog){
 	int listenRet = listen(socket, backlog);
 	if(listenRet <0){
 		perror("Error binding");
 		exit(-1);
 	}
 	return(listenRet);

 }
  int Accept(int socket, struct sockaddr *address, socklen_t *addresslen){
 	int acceptRet = accept(socket, address, addresslen);
 	if(acceptRet <0 ){
 		perror("Error binding");
 		exit(-1);
 	}
 	return(acceptRet);
 }

 ssize_t SendTo(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len){
  int sendRet = sendto(socket, buffer, length, flags, dest_addr, dest_len);
  if(sendRet<0){
    perror("Error sending");
    exit(-1);
  }
  return(sendRet);
 }

ssize_t Recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len){
  int recvRet = recvfrom(socket, buffer, length, flags, address, address_len);
  if(recvRet<0){
    perror("Error receiving");
    exit(-1);
  }
  return(recvRet);
}








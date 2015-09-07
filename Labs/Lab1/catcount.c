//Elias Strizower

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


extern char **environ;
void print_environment(void);

int main(int argc, char* argv[]){

  print_environment();

  pid_t pid;
  pid_t pid2;

  if ((pid = fork()) == 0) {
    //child process
    execlp("/bin/cat","/bin/cat", argv[1],(char *)NULL);
  } 
  else {

    //parent process
    wait(pid);

  }
  if ((pid2 = fork()) == 0) {
    //child process 2
    execlp("/usr/bin/wc", "/usr/bin/wc", argv[1],(char *)NULL);
  }
  else {
    //parent process 2
    wait(pid2);
    exit(0);
    
  }
}
  void print_environment(void){
    int i = 0;
    while (environ[i] != NULL){
      printf(environ[i]);
      printf("\n");
      i++;

    }
  }





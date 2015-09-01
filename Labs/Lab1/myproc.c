#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char* main(int argc, char*str)
{

  int pid = fork();
  int num = 0;

 
  if (pid<0){
   printf("fork error");
  }else if (pid == 0) {    //child1

    while(1){
 
    printf("Child: %d\n ", num);
        num++;
    }
  }else if (pid == 1) {    //child
 
     printf("Child2: ");
      printf("%d\n",num);
        num++;
  }
  
  else {   //parent
     
     printf("Parent: "); 
     printf("%d\n", num);
    num++;
  

  }
}

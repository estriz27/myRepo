/*
 * CSCI 315 Operating Systems Design
 * Date: 2014-09-02
 * Copyright (c) 2014 Bucknell University
 *
 * Permission is hereby granted, free of charge, to any individual or
 * institution obtaining a copy of this software and associated
 * documentation files (the "Software"), to use, copy, modify, and
 * distribute without restriction, provided that this copyright and
 * permission notice is maintained, intact, in all copies and supporting
 * documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int i = 7;
double x = 3.14;

pid_t Fork(void) {
  pid_t pid;
  if ((pid = fork()) == -1){
    perror("Error creating child process");
    exit(-1);
  }
  else {
    return pid;
  }


}

int main(int argc, char* argv[]) {

  int pid;
  int j = 6;
  double y = 2.18;



  
  char buf_parent[5];
  char buf_child[5]; 
  int status; // exit status to be filled by wait

  // create and open a file called data.txt

  // write into data.txt the following string:
  // "this is a test for processes created with fork\nthis is another line"

  int file  = open("data.txt",O_RDWR);
  write(file, "this is a test for processes created with fork\nthis is another line", 40);

  if ((pid = fork()) == 0) {
    // child process
    
    // read 5 characters from file into buf_child
    // print the characters in buf_child to terminal

    int file = open("data.txt", O_RDONLY);
    read(file,buf_child,5);
    write(1,buf_child,5);
    close(file);
  
    // close the file

    exit(0);

  } else {

    // parent process

    printf("pid= %d -- parent waits for child to terminate\n", pid);
    printf("pid= %d -- before wait parent sees x= %lf, y=%lf\n", pid, x, y);

    // read 5 characters from file into buf_parent
    // print the characters in buf_parent to terminal

    
    int file = open("data.txt", O_RDONLY);
    read(file,buf_parent,5);
    write(1,buf_parent,5);


 
    



    wait(&status); // note we are not catching the return value of wait!
    printf("parent got termination status= %d from child\n", status);
    printf("pid= %d -- after wait sees x= %lf, y=%lf\n", pid, x, y);

    // read another 5 characters from file into buf_parent
    // print the characters in buf_child to terminal

    
    read(file,buf_parent,5);
    write(1,buf_parent,5);
    close(file);   
    
    // close the file

    printf("parent is terminating\n");
    exit(0);
  }

}

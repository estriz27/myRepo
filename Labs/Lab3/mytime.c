//Elias Strizower
//Lab 3 prelab

#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  struct timeval myTime;
    gettimeofday(&myTime, NULL);
  time_t timeStr = myTime.tv_sec;
  printf("%s", ctime(&timeStr));


}

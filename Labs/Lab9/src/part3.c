#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocator.h"
#include <limits.h>

extern struct dlist *allocated_list;
extern struct dlist *free_list;

void part3(int algorithm, unsigned int seed, int requests){
  double d;
  int alloc = allocator_init(10240);
  if (alloc == 0){
    // printf("Successfully initialized allocator\n");
  }
  else{
    printf("Error initializing allocator\n");
  }

  srandom(seed);
  int r = 0;
  void *p = NULL;
  long int s = 0;
  while (r<requests){
    s = (((float)random() / INT_MAX) * 900)+ 100;

    p = allocate(s, algorithm);

  if (s >=500){
    deallocate(p);
  }
  r++;
	
}
d = average_frag();
printf("%f\n",d);
  
}

int main(){
  printf("First Fit:\n");
  for (int x = 0; x <=34; x++){
    part3(0,x,30);
  }
  printf("Best Fit:\n");
  for (int x=0; x<=34; x++){
    part3(1,x,30);
  }
  printf("Worst Fit:\n");
  for (int x=0; x<=34; x++){
    part3(2,x,30);
  }

}


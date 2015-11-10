#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocator.h"
#include <limits.h>



int main(int argc, char *argv[]) {
  double d;
  int algorithm;
  unsigned int seed;
  int requests;

  if (argc == 4){
    algorithm = atoi(argv[1]);
    seed = atoi(argv[2]);
    requests = atoi(argv[3]);
    printf("successfull input of inputs\n");
  }
  else{
    printf("%s: [algorithm][seed][int requests]", argv[0]);
    exit(-1);
  }

	int alloc = allocator_init(10240); 
	
	if (alloc == 0){
		printf("Successfully created allocator\n");
	}
	else{
		printf("Error creating allocator\n");
	}


	srandom(seed);
	int r = 0;
	void *p = NULL;
	long int s = 0;
	while (r<requests){
	  s = (((float)random() / INT_MAX) * 900)+ 100;

	  if ((p = allocate(s, algorithm)) == NULL){
	  }
	  if (r >=500){
	    deallocate(p);
	  }
	  r++;
	
	}
	 d = average_frag();
	 printf("%.2f\n",d);

}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocator.h"



int main() {

	int alloc = allocator_init(1000); 
	
	if (alloc == 0){
		printf("Successfully created allocator\n");
	}
	else{
		printf("Error creating allocator\n");
	}
	
	//test of first fit
      	allocate(50,0);
	//test of best fit
	allocate(50,1);
	//tests to see if deallocate works
	void *p = allocate(100,2);
	deallocate(p);
	allocate(50,1);
	allocate(1000,1);
	//test of worst fit
	allocate(50,2);
	allocate(50,2);

}

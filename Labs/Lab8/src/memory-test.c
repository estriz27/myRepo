#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocator.h"
#include "allocator.c"



int main() {

	int alloc = init_allocator(1000); 
	if (alloc == 0){
		printf("Successfully created allocator\n");
	}
	else{
		printf("Error creating allocator\n");
	}
	return 0;

	allocate(50, 1);

	allocate (50, 2);

	allocate(50,3);

	allocate (5000, 1);
}
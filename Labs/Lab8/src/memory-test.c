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
	

	allocate(50, 1);

}
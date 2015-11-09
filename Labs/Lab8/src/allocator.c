#include "allocator.h"
#include "dlist.h"
#include "dnode.h"
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <stddef.h>

	struct dlist *free_list;
	struct dlist *allocated_list;

int allocator_init(size_t size){

	free_list = dlist_create();

	allocated_list = dlist_create();

	void *p = malloc(size);
	if (p == NULL){
		return -1;
	}
	else{
	  dlist_add_back(free_list, p,size);
		return 0;
	}

}

void *allocate(size_t size, int type){
  /*  printf("print:\n");
	struct dnode* nodeA;
	struct dnode* nodeB;
	for(nodeA = dlist_iter_begin(free_list); nodeA!= NULL; nodeA = dlist_iter_next(free_list)){
	  printf("%p\n",nodeA->data);
	}
	for(nodeB = dlist_iter_begin(allocated_list); nodeB!= NULL; nodeB = dlist_iter_next(allocated_list)){
	  printf("%p\n",nodeB->data);
	}*/

  struct dnode* node = NULL;
	if(type == 0){
		node = firstFit(free_list,size);

	}
	else if(type ==1){
		node = bestFit(free_list, size);
	}
	else if(type ==2){
		node = worstFit(free_list,size);
	}
	else{
		printf("Please enter either 0, 1, or 2");	
		}

	if (node != NULL){
			void *temp = node->data;
			dlist_add_back(allocated_list, temp,size);
			dlist_add_back(free_list,temp + size, node->size - size);
		      	dlist_find_remove(free_list,temp);
			return(temp);

		}
		return NULL;
		
	}

	
struct dnode* firstFit(struct dlist *l, size_t size){
	struct dnode* node;
	for(node = dlist_iter_begin(l); node!= NULL; node = dlist_iter_next(l)){
	  printf("looking at node, for size %zu, size is %zu\n", size, node->size);
		if (node->size > size){
			return node;
		}
	}
	return NULL;
}

struct dnode* bestFit(struct dlist *l, size_t size){
	struct dnode* node;
	struct dnode* temp = NULL;
	int currSize = INT_MAX;
	printf("For loop started\n");
	for(node = dlist_iter_begin(l); node!= NULL; node = dlist_iter_next(l)){
	  printf("looking at node, for size %zu, size is %zu\n", size, node->size);
		if (node->size >= size && node->size < currSize){
 
			temp = node;
			currSize = temp->size;
		}

	}
	printf("For loop complete\n");
		if (temp != NULL){
			printf("returned temp\n");
			return temp;
		}
		else{
			printf("returning null\n");
			return NULL;
		}
	}

struct dnode* worstFit(struct dlist *l, size_t size){
	struct dnode *node;
	struct dnode *temp;
	int currSize = 0;
	for(node = dlist_iter_begin(l); node!= NULL; node = dlist_iter_next(l)){
	  printf("looking at node, for size %zu, size is %zu\n", size, node->size);
		if(node->size > size && node->size > currSize){
			temp = node;
			currSize = temp->size;

		}
	}
		if(temp!= NULL){
		  printf("returned pointer\n");
			return temp;
		}
		else{
		  printf("returned null\n");
			return NULL;
		}

}

int deallocate(void *ptr){
	struct dnode *node;
	for(node = dlist_iter_begin(allocated_list);node!= NULL; node = dlist_iter_next(allocated_list)){
		if(node->data == ptr){
		  dlist_add_back(free_list,node,node->size);
			dlist_find_remove(allocated_list,node);
			return 0;
		}
	}
	return -1;

}

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
		dlist_add_back(free_list, p);
		return 0;
	}

}

void *allocate(size_t size, int type){
	struct dnode* node;
	if(type == 0){
		node = firstFit(free_list,size);
		if (node->data != NULL){
			void *temp = node->data;
			dlist_find_remove(free_list,temp);
			dlist_add_back(allocated_list, temp);
			return(temp);

		}

	}
	else if(type ==1){
		node = bestFit(free_list, size);
		if(node->data != NULL){
			void *temp = node->data;
			dlist_find_remove(free_list,temp);
			dlist_add_back(allocated_list,temp);
			return(temp);
		}

	}
	else if(type ==2){
		node = worstFit(free_list,size);
		if(node->data != NULL){
			void *temp = node->data;
			dlist_find_remove(free_list,temp);
			dlist_add_back(allocated_list,temp);
			return(temp);
		}

	}
	else{
		printf("Please enter either 0, 1, or 2");	
		}
		return NULL;

	}
	
struct dnode* firstFit(struct dlist *l, size_t size){
	struct dnode* node;
	for(node = dlist_iter_begin(l); node!= NULL; node = dlist_iter_next(l)){
		if (node->size > size){
			return node;
		}
	}
	return NULL;
}

struct dnode* bestFit(struct dlist *l, size_t size){
	struct dnode* node;
	struct dnode* temp;
	int currSize = INT_MAX;
	printf("For loop started\n");
	for(node = dlist_iter_begin(l); node!= NULL; node = dlist_iter_next(l)){
		if (node->size > size && node->size < currSize){
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
		if(node->size > size && node->size > currSize){
			temp = node;
			currSize = temp->size;

		}
	}
		if(temp!= NULL){
			return temp;
		}
		else{
			return NULL;
		}

}

int deallocate(void *ptr){
	struct dnode *node;
	for(node = dlist_iter_begin(allocated_list);node!= NULL; node = dlist_iter_next(allocated_list)){
		if(node->data == ptr){
			dlist_add_back(free_list,node);
			dlist_find_remove(allocated_list,node);
			return 0;
		}
	}
	return -1;

}

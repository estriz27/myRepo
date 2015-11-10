#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <stddef.h>
#include "dlist.h"


int allocator_init(size_t size);

void *allocate(size_t size, int type);

struct dnode* firstFit(struct dlist *l, size_t size);

struct dnode* bestFit(struct dlist *l, size_t size);

struct dnode* worstFit(struct dlist *l, size_t size);

int deallocate(void *ptr);

//Average_frag works by calculating the amount of free space 
//and then dividing it by the number of nodes in free_list
double average_frag();

#endif

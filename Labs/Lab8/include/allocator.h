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

#endif

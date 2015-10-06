/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdlib.h>
#include "circular-list.h" 
#include <stdio.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <pthread.h>



//use mutex in pthreads library
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int circular_list_create(struct circular_list *l, int size) {
  l->buffer = calloc(size, sizeof(item));
  l->start = -1;
  l->end = -1;
  l->elems = 0;
  l->size = size;

  //initialize semaphores and mutex
 // pthread_mutex_init(&mutex, NULL);
  sem_init(&empty, 1, l->size);
  sem_init(&full, 1, 0);


  return 0;
}

int circular_list_insert(struct circular_list *l, item i) {
  //if elems < size.   l->buffer[elems]%size 
  //move start when remove
  //move end when you insert, if there is space, or return error
  pthread_mutex_lock(&mutex);
  sem_wait(&empty);

    if (l->elems >= l->size){
        printf("Error, list is full\n");
        return -1;
      }
    if(l->elems == 0){
      l->start = 0;
      l->end = 0;
      l->buffer[0] = i;
      l->elems +=1;

    }
    else{
      l->end = ((l->end +1)%l->size);
      l->buffer[l->end] = i;
      l->elems+=1;
    } 
   
    pthread_mutex_unlock(&mutex);
    sem_post(&full);

    return 0;

    
    
  

}

int circular_list_remove(struct circular_list *l, item *i) {
  pthread_mutex_lock(&mutex);
  sem_wait(&full);
	if(l->elems > 0){
		*i = l->buffer[l->start];
    l->start= ((l->start +1)%l->size);
    l->elems -=1;
		}
		
	else{
		printf("Error, list is empty\n");
    return(-1);
	}
  pthread_mutex_unlock(&mutex);
  sem_post(&empty);
  return 0;
}

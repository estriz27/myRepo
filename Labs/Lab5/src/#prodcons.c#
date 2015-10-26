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
#include <stdio.h>
#include <stdbool.h> 
#include <unistd.h>
#include <pthread.h>
#include <sys/sem.h>
#include <semaphore.h>
#include "circular-list.h" 

/* SCALE_FACTOR is a constant for you to experiment with:
 * if you choose a very large SCALE_FACTOR, your threads
 * might spend a long time sleeping. If you choose it to be
 * too small, your threads will not sleep at all. Note
 * that in the producer and consumer functions, the sleep
 * time is computed as the INTEGER DIVISION below:
 *
 *  usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX
 *
 *  where RAND_MAX is the largest random numver returned
 *  by rand_r. If the numerator is smaller than RAND_MAX,
 *  the quotient of the integer division is ZERO!
 */
#define SCALE_FACTOR 1000

// global variables -----------------------

struct circular_list mylist;
int baseseed = 1738;

// end of global variables ----------------

void *producer (void *param) {
  item i;
  unsigned int seed = *((int *) param);
  int randSeed = rand_r(&seed);
  printf("randSeed = %d\n", randSeed);
  while (true) {
    
    
    
    // sleep for random period of time
    printf("producer going to sleep\n");
    usleep(SCALE_FACTOR * randSeed / RAND_MAX); 
    printf("producer waking up\n");

    randSeed = rand_r(&seed);
    
    // generate a random number
    i = (item) (((double) randSeed) / RAND_MAX);

    if (circular_list_insert(&mylist, i) == -1) {
      printf("PRODUCER: error condition\n");
    } else {
      printf("PRODUCER: produced value %lf\n", i);
    }
  }
  
  
}

void *consumer (void *param) {
  item i;
  unsigned int seed = *((int *) param);
  int randSeed = rand_r(&seed);
  printf("randSeed = %d\n", randSeed);

  while (true) {
    // sleep for random period of time
    
    
    usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX);

    if (circular_list_remove(&mylist, &i) == -1) {
      printf("CONSUMER: error condition\n");
    } else {
      printf("CONSUMER: consumed value %lf\n", i);
    }
  }

}

int main (int argc, char *argv[]) {
//declare command line arguments
int num_prod;
int num_cons;
float sltme;

    //check for all command line arguments
  if(argc< 4){
    printf("Missing Command Line Argument");
    exit(-1);
  }


  // get command line arguments
  num_prod = atoi(argv[1]);   //# of producer threads
  num_cons = atoi(argv[2]);   //# of consumer threads
  sltme = atof(argv[3]);  //sleep time


  //declare thread variables

  pthread_t *tidprod;
  pthread_t *tidcons;

  tidprod = (pthread_t *)calloc(num_prod, sizeof(pthread_t));
  tidcons = (pthread_t *)calloc(num_cons, sizeof(pthread_t));

  // initialize buffer
  circular_list_create(&mylist, 20);

  // create producer thread(s)
  for( int i = 0; i< num_prod; ++i){
      int *seed = malloc(sizeof(int));
      *seed = baseseed + i;
     int error = pthread_create(&tidprod[i], NULL, producer, (void *) seed);
     if(error){
      printf("Error creating threads");
      exit(-1);
     }
  }
  // create consumer thread(s)
 for( int i = 0; i< num_cons; ++i){
     int *seed = malloc(sizeof(int));
     *seed = baseseed +i;
     int error = pthread_create(&tidcons[i],NULL, consumer, (void *) seed);
     if(error){
      printf("Error creating threads");
      exit(-1);
    }
  }
  // sleep to give time for threads to run
  usleep(sltme* 1000000);
  printf("Exiting\n");
  
  // exit
  return (0);
}

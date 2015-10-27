//Elias Strizower
//Prelab 7

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* Philosopher(void *);
void napping(int);
 

void* Philosopher(void *id){
  while(1){
    long long id2 = *(long long*)id;
  printf("Philosopher %llu is thinking\n",id2);
    napping(1);
    printf("Philosopher %llu is hungry\n", id2);
    printf("Philosopher %llu is starting to eat\n", id2);
    napping(2);
    printf("Philosopher %llu is done eating\n", id2);

  }
 }

int main (int argc, char *argv[]) {
  int i;
  pthread_t tids[5];
  long long array[] = {0,1,2,3,4};

  //tids = (pthread_t *)calloc(5, sizeof(pthread_t));
  //threads take a pointer so id is a reference to the point in the array for which it were assigned.
  //if array values were changed, the id's would be changed too
  for(i = 0; i< 5; i++){
    int error = pthread_create(&tids[i], NULL, Philosopher,(void *)&array[i]);
      if(error){
      printf("Error creating threads");
      exit(-1);
      }
  }
   pthread_exit(NULL);
   return(0);
}

void napping(int t){
   usleep((rand_r(&t)/t)*10000000); 
}

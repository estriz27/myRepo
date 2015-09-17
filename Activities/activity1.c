//Elias Strizower and Ryan Stecher
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <inttypes.h>

int summation(int x, int y);
void *sum(void * args);

  struct argument_struct{
    int x;
    int y;
  };

pthread_t tid1;
pthread_t tid2;




int summation(int i , int j){
  int first = i;
  int last = j;
  int middle = j/2 -1;

  struct argument_struct * arg1;
  arg1 = (struct argument_struct *) calloc(1, sizeof(struct argument_struct));
  arg1->x = first;
  arg1->y = middle;
  
  struct argument_struct * arg2;
  arg2 = (struct argument_struct *) calloc(1,sizeof(struct argument_struct));
  arg2->x = middle;
  arg2->y = last;
  
  
  int firstHalf = pthread_create(&tid1,NULL, &sum, (void **) arg1);
  int secondHalf = pthread_create(&tid2, NULL, &sum, (void **) arg2);

  int firstHalfSum;
  int final;
  pthread_join(tid1, (void *) &firstHalfSum);
  final = final + firstHalfSum;

  int secondHalfSum;
  pthread_join(tid2, (void *) &secondHalfSum);
  final = final + secondHalfSum;
  
  return final;


}


int main(int argc, char* argv[]){
  int n = atoi(argv[1]);
  int result = summation(0, n);
  
  printf("The sum of %d from 1 to %d is: %d\n", n,n,result);



  

}


void *sum(void * args){
  struct argument_struct *arg = (struct argument_struct *) args;
  int sum = 0;
  int a = arg->x;
  int b = arg->y;
  while(a< b){
    a++;
    sum += a;
  }

  pthread_exit((void*) sum);
}


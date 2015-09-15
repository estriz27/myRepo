//Elias Strizower
//Lab 3 prelab
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *t1();
void *t2();
void *t3();
void t4();

  pthread_t tid1;
  pthread_t tid2;
  pthread_t tid3;

  char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
  int counter = 0;
  int t2c = 0;
  int i;


int main(int argc, char* argv[]){


  while(1){
  tid1 =  pthread_create(&tid1, NULL, &t1, NULL);
  tid2 = pthread_create(&tid2, NULL, &t2, NULL);
  tid3 = pthread_create(&tid3, NULL, &t3, NULL);
  }
}
 
  void t4(){
    int sum = 0;
    for (i = 0; i <= 10000; i++){
      sum += i;
    }
  }

  void *t1(){
    printf("%d\n",counter);
    counter ++;
    counter = counter%10;
    t4();
  }
  
  void *t2(){

    char currchar = alphabet[t2c];
    printf("%c\n", currchar);
    t2c ++;
    t2c = t2c%25; 
    t4();
  }
  
  void *t3(){
    printf("#\n");
    t4();
  }


      


  
  

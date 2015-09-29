#include "circular-list.c"
#include "circular-list.h"

int main(){

item myItem = 0.0;
item myItem1 = 3.0;
item myItem2 = 4.0;
item myItem3 = 5.0;

struct circular_list myList;


//& passes address of struct
//* makes pointer not a pointer

circular_list_create(&myList, 2);


circular_list_insert(&myList, myItem1);
printf("Inserted value %f\n", myItem1);

circular_list_insert(&myList, myItem2);
printf("Inserted value %f\n", myItem2);

circular_list_insert(&myList, myItem3);
printf("Inserted value %f\n", myItem3);

circular_list_remove(&myList, &myItem);
printf("Removed value %f\n", myItem);

circular_list_remove(&myList, &myItem);
printf("Removed value %f\n", myItem);

circular_list_remove(&myList, &myItem);
printf("Removed value %f\n", myItem);

}
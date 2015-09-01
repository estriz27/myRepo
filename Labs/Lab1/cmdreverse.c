//Elias Strizower
//CSCI 315 Prelab 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* main(int argc, char *argv[])
{

char *string = malloc(strlen(argv[1]+1));
 strcpy(string, argv[1]);
 int len = strlen(argv[1]);


 if (argc == 2) {    //if there is on parameter passed into the function
   while (len>=0){
         printf("%c", string[len]);
          len --;
    }
   printf("\n");

 } else{
   printf("Failed\n");
   }
}



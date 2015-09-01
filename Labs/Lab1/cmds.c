//Elias Strizower
//CSCI 315 Prelab 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char first;
	int second;
	float third;
	char *fourth = malloc(strlen(argv[4]+1));

//check if 4 parameters are provided

if (argc == 5) {

	first = *argv[1];
	second = atoi(argv[2]);
	third = strtof(argv[3],NULL);
	strcpy(fourth, argv[4]);
	//else exit
	
	printf("%c\n%d\n%f\n%s\n",first,second,third,fourth);

}
else{
	printf("%s", "failure\n");
exit(0);



}

}



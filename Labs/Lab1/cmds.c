//Elias Strizower
//CSCI 315 Prelab 1

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char first;
	int second;
	float third;
	char fourth[20];

//check if 4 parameters are provided

if (argc == 5) {

	first = *argv[1];
	second = *argv[2];
	third = *argv[3];
	strcpy(fourth, *argv[4]);
	//else exit
	
	printf("%c\n%d\%f.2\n%s\n",first,second,third,fourth);

}
else{
	printf("%s", "failure");
exit(0);



}

}



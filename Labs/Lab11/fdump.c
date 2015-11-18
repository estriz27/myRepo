
#include <stdlib.h>
#include <stdio.h>
#include "hexdump.h"

int main(int argc, char *argv[]){

	char *filename;
	unsigned int offset;
	unsigned int size;


if (argc == 4){
	filename = argv[1];
	offset = atoi(argv[2]);
	size = atoi(argv[3]);
	}
	else{
	printf("%s usage: [filename] [offset] [size]\n", argv[0]);
    exit(-1);
}

	

	FILE * fp = fopen(filename, "r");
	fseek(fp,offset,SEEK_SET);

	unsigned char *buffer = malloc(sizeof(char) * 250);
	fread(buffer, size, 1, fp);
	hexdump(buffer, size);
	fclose(fp);

}
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

struct account {
	int id;
	char name[80];
	double balance;
};

int main(int argc, char *argv[]){
	struct account myAccount = {10, "myAccount", 100.0};
	int fp = open("account.txt", O_CREAT | O_RDWR);
	write(fp, &myAccount, sizeof(myAccount));
	close(fp);
}

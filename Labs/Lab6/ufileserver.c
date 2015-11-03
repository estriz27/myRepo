#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "readwrite.h" 
#include <pthread.h>
#include <semaphore.h>
#include <sys/sem.h>

#define MAX_FILE_PATH   257 // length of path+filename and null char  
#define BUFFER_SIZE     512 // size of file read buffer    
#define	QLEN		6   // size of request queue
int	visits	    =   0;  // counts client connections
int     fileReq     =   0;
int     statReq     =   0;
int     filenFnd    =   0;
int     avgFilReq   =   0;

/*------------------------------------------------------------------------
 * Program:   fileserver
 *
 * Purpose:   allocate a socket and then repeatedly execute the following:
 *		(1) wait for the next connection from a client
 *		(2) send a short message to the client
 *		(3) close the connection
 *		(4) go back to step (1)
 *
 * Syntax:    fileserver [ port ]
 *
 *		 port  - protocol port number to use
 *
 *------------------------------------------------------------------------
 */

void* process_request(void* fd);

struct values{


  int numFileReq;
  int numStatReq;
  int numFNF;
  int avgLen;
};

struct values structVals = {0,0,0,0};
pthread_mutex_t mutex;
sem_t mySem;



int main(int argc, char* argv[]) {
	struct sockaddr_in sad;  // structure to hold server's address	
	struct sockaddr_in cad;  // structure to hold client's address	
	int sd, sd2;	           // socket descriptors			
	int port;		             // protocol port number		
	socklen_t alen;          // length of address			
	int pid;                 // process id
	pthread_t tid;           //declare thread id

	struct message { 
	  char type; 
	  int order;
	} msgbuf;
    msgbuf.order = 0;
	
	sem_init(&mySem,0,5);


	pthread_mutex_init(&mutex,NULL);

	memset((char *)&sad,0,sizeof(sad)); // clear sockaddr structure	
	sad.sin_family = AF_INET;	          // set family to Internet	        
	sad.sin_addr.s_addr = INADDR_ANY;   	

	// Check command-line argument for protocol port
	if (argc > 1) {			
		port = atoi(argv[1]);	        
	}
	else {
		printf("Usage: fileserver [ port ]\n");
		exit(-1);
	}

	if (port > 0)	 // data structure for a message


		// test for illegal value	
		sad.sin_port = htons((u_short)port);
	else {				
		// print error message and exit	
		fprintf(stderr,"SERVER: bad port number %s\n",argv[1]);
		exit(1);
	}

	// Create a socket 
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		fprintf(stderr, "SERVER: socket creation failed\n");
		exit(1);
	}
	

	// Bind a local address to the socket 
	Bind(sd, (struct sockaddr *)&sad, sizeof(sad));

	// Specify size of request queue 
	Listen(sd, QLEN);

	// Main server loop - accept and handle requests 
	while (1) { // it is a daemon, so infinite loop is ok
	        sem_wait(&mySem);
		alen = sizeof(cad);

		sd2 = Accept(sd, (struct sockaddr *)&cad, &alen);

		visits++;
		
	       	
	        pthread_create(&tid, NULL, process_request, (void*) (intptr_t)sd2);
		
	}

	close(sd); // parent closes connected socket
	return(0); // will never get here, but to shut up the compiler
}

void* process_request(void* param)
{
       
        int fd = (intptr_t)param;
	char buf[BUFFER_SIZE];  // buffer for file chunk server sends	
	char reqbuf[MAX_FILE_PATH];
	int file_req;
	int bytes_read;     
	int bytes_expected;
	int cc;


	// Read request for fileserver
	// first red the length of incoming string

	Readn(fd, &bytes_expected, sizeof(int));
	Readn(fd, reqbuf, bytes_expected);
	
	  cc = Recvfrom(socket_fd, &message, sizeof(msg), 0, (struct sockaddr *) &from, &fsize);
	  printsin( &from, "recv_udp: ", "Packet from:");

	reqbuf[bytes_expected] = 0;

	if (strncmp(message.type, "get", 4) == 0) {
		// Request is "get file", so now read full path to file
		// Pre-condition: full path string is no more than 256 chars long
		// now read the length of the file name
		Readn(fd, &bytes_expected, sizeof(int));
		

		// read the actual file name
		Readn(fd, reqbuf, bytes_expected);

		reqbuf[bytes_expected] = 0; // terminate the string

		printf("SERVER: file requested is %s\n", reqbuf);
		fflush(stdout);

		pthread_mutex_lock(&mutex);
		structVals.numFileReq++;
		structVals.avgLen = ((structVals.avgLen * (structVals.numFileReq -1) + bytes_expected)/structVals.numFileReq);
		pthread_mutex_unlock(&mutex);

		


		if ((file_req = open(reqbuf,O_RDONLY)) == -1) {
			printf("SERVER: file not found\n");

			pthread_mutex_lock(&mutex);
			structVals.numFNF++;
			pthread_mutex_unlock(&mutex);

			fflush(stdout);
		} 
		else {
			printf("SERVER: file %s found\n", reqbuf);
			fflush(stdout);

			do {
				bytes_read = Readn(file_req, buf, BUFFER_SIZE);
				Writen(fd, buf, bytes_read);
			} while (bytes_read > 0);
			
		}
	}
	else if (strncmp(reqbuf, "stats", 6) == 0) {
		// Request is "get stats"
	  pthread_mutex_lock(&mutex);
	  structVals.numStatReq++;
	  
		printf("SERVER: stats requested");

		sprintf(buf,"Server has been contacted %d time%s\nNumber of files not found is %d\nNumber of file requests is %d\nNumber of status requests served is %d\nAverage length of file requests is %d\n ",
			visits,visits==1?".":"s.",structVals.numFNF,structVals.numFileReq, structVals.numStatReq, structVals.avgLen);
		pthread_mutex_unlock(&mutex);
		bytes_expected = strlen(buf);
		Writen(fd, &bytes_expected, sizeof(int));
		Writen(fd, buf, bytes_expected);
	}
	else {
		// Request is invalid
		printf("SERVER: invalid request\n");
	}
	close(fd);
	sem_post(&mySem);
	//closed fd when everything in this method is done. if put afte thread create, may close before process is done executing
}

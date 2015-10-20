CC   = gcc
CFLAGS = -g 
LFLAGS = -lpthread
ALL  = send_udp recv_udp getstats fileserver getfile

all : $(ALL)

recv_udp: recv_udp.c wrappers.o 
	$(CC) $(CFLAGS) wrappers.o recv_udp.c -o recv_udp

send_udp: send_udp.c wrappers.o
	$(CC) $(CFLAGS) wrappers.o send_udp.c -o send_udp

getfile: getfile.c wrappers.o readwrite.o
	$(CC) $(CFLAGS) wrappers.o readwrite.o getfile.c -o getfile

fileserver: fileserver.c wrappers.o readwrite.o
	$(CC) $(CFLAGS) $(LFLAGS) wrappers.o fileserver.c readwrite.o -o fileserver 

getstats: getstats.c wrappers.o readwrite.o
	$(CC) $(CFLAGS) wrappers.o readwrite.o getstats.c -o getstats

readwrite.o: readwrite.c readwrite.h
	gcc -c readwrite.c -o readwrite.o

wrappers.o: wrappers.c wrappers.h
	gcc -c wrappers.c -o wrappers.o

clean:
	/bin/rm -f *.o *~ core $(ALL)

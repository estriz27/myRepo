CC   = gcc
CFLAGS = -g 
LFLAGS = -lpthread
ALL  = send_udp recv_udp getstats fileserver getfile

all : $(ALL)

recv_udp: recv_udp.c wrappers.o 
	$(CC) $(CFLAGS) wrappers.o recv_udp.c -o recv_udp

send_udp: send_udp.c wrappers.o
	$(CC) $(CFLAGS) wrappers.o send_udp.c -o send_udp

getfile: getfile.c 
	$(CC) $(CFLAGS) getfile.c -o getfile

fileserver: fileserver.c
	$(CC) $(CFLAGS) fileserver.c -o fileserver

getstats: getstats.c
	$(CC) $(CFLAGS) getstats.c -o getstats

wrappers.o: wrappers.c wrappers.h
	gcc -c wrappers.c -o wrappers.o

clean:
	/bin/rm -f *.o *~ core $(ALL)

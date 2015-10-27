CC   = gcc
CFLAGS = -g 
LFLAGS = -lpthread
<<<<<<< HEAD
ALL  = send_udp recv_udp getstats fileserver getfile
=======
ALL  = send_udp recv_udp ugetstats ufileserver ugetfile
>>>>>>> 4c061d65fbca0e5bb544a718d5d92906794d4c3a

all : $(ALL)

recv_udp: recv_udp.c wrappers.o 
	$(CC) $(CFLAGS) wrappers.o recv_udp.c -o recv_udp

send_udp: send_udp.c wrappers.o
	$(CC) $(CFLAGS) wrappers.o send_udp.c -o send_udp

<<<<<<< HEAD
getfile: getfile.c 
	$(CC) $(CFLAGS) getfile.c -o getfile

fileserver: fileserver.c
	$(CC) $(CFLAGS) fileserver.c -o fileserver

getstats: getstats.c
	$(CC) $(CFLAGS) getstats.c -o getstats
=======
ugetfile: ugetfile.c wrappers.o readwrite.o
	$(CC) $(CFLAGS) wrappers.o readwrite.o ugetfile.c -o ugetfile

ufileserver: ufileserver.c wrappers.o readwrite.o
	$(CC) $(CFLAGS) $(LFLAGS) wrappers.o ufileserver.c readwrite.o -o ufileserver 

ugetstats: ugetstats.c wrappers.o readwrite.o
	$(CC) $(CFLAGS) wrappers.o readwrite.o ugetstats.c -o ugetstats

readwrite.o: readwrite.c readwrite.h
	gcc -c readwrite.c -o readwrite.o
>>>>>>> 4c061d65fbca0e5bb544a718d5d92906794d4c3a

wrappers.o: wrappers.c wrappers.h
	gcc -c wrappers.c -o wrappers.o

clean:
	/bin/rm -f *.o *~ core $(ALL)

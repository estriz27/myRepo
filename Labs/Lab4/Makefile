CC = gcc

CFLAGS = 
DEPS = wrappers.h

all: echod echoreq echoreq2
#Line makes all of the .o files through substitution as opposed to having multiple
%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)
#make echod depends on echod.o and wrappers.o
echod: echod.o wrappers.o
	$(CC) echod.o wrappers.o -o echod
#make echoreq echoreq.o and wrappers.o
echoreq: echoreq.o wrappers.o
	$(CC) echoreq.o wrappers.o -o echoreq 

echoreq2: echoreq2.o wrappers.o
	$(CC) echoreq2.o wrappers.o -o echoreq2




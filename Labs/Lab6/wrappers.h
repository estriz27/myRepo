//Elias Strizower
#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/socket.h>

int Fork(void);

int Pipe(int pipefd[2]);

int Read(int fd, void *buf, size_t count);

int Write(int fd, const void *buf, size_t count);

int Wait(int *wait);

int Waitpid(pid_t pid, int *stat_loc, int options);

int Open(const char *path, int log);

int Close(int fildes);

int Connect(int socket, const struct sockaddr *address, socklen_t addresslen);

int Bind(int socket, const struct sockaddr *address, socklen_t addresslen);

int Listen(int socket, int backlog);

int Accept(int socket, struct sockaddr *address, socklen_t *addresslen);

ssize_t Recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len);

ssize_t SendTo(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);




#endif

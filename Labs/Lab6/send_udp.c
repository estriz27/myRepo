/*
 * Copyright (c) 2015 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "wrappers.h"

#define MYPORT 1738

int main(int argc, char *argv[])
{
  int socket_fd;

  // address of destination socket
  struct sockaddr_in  dest;

  // pointer to host data structure
  struct hostent *hostptr;
  
  // data structure for a message
  struct message { 
    char head; 
    u_long body; 
    char tail; 
  } msgbuf;
  
  // This creates a socket and assigns is to socket_fd
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  // Clears the memory for the socket
  memset((void*) &dest, 0, sizeof(dest));

  // Assigns an internet host by referencing it to a pointer
  hostptr = gethostbyname(argv[1]);

  // Assigns a protocal to the socket. AF_INET refers to addresses from the internet, specifically IP addresses
  dest.sin_family = (short) AF_INET;

  // Copies h->length bytes of h_addr to the dest address
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);

  // Set destination port number
  dest.sin_port = htons((u_short) MYPORT);

  // build message to send
  msgbuf.head = '<';

	// Converts the pid between host and network byte number and stores in in body
	msgbuf.body = htonl(getpid());
  msgbuf.tail = '>';

  // Sends message from one socket to another
  SendTo(socket_fd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&dest, sizeof(dest));

  return 0;
}

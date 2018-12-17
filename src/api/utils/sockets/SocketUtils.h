#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <string.h>
#include <unistd.h>

#include "../exceptions/SocketException.h"

/**
 * Socket Utilities
 *
 * A wrapper for the Unix socket library
 * 
 */

class SocketUtils {

private:

	int socketfd;
	struct sockaddr_in sock;

	char* hostnameToIP(const char * hostname);

public:

	SocketUtils(int port);
	SocketUtils(const char* hostname, int port);

	~SocketUtils();

	void connectToHost();
	void disconnectFromHost();
	
	void sendData(const char* data);
	void receiveData(int size, char buffer[size]);

};

#endif
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

class SocketUtils {

private:

	int socketfd;
	struct sockaddr_in sock;

	char* hostnameToIP(const char * hostname);

public:

	SocketUtils();
	SocketUtils(const char* hostname, int port);

	void connectToHost();
	void sendData(const char* data);
	void receiveData(const char* data, int size, char buffer[size]);

};

#endif
#ifndef DOMAIN_SOCKET_UTILS_H
#define DOMAIN_SOCKET_UTILS_H

#include <memory>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <thread>

#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "../exceptions/SocketException.h"

/*
 * Domain Socket Utilities
 *
 * A basic utility to faciliate domain socket communications with a Node.JS backend.
 * Not sure if this will actually be usefull in the future; I misread the Spotify documentation 
 * and thought I could use this method to stream audio.
 *
 */

class DomainSocketUtils {

private:

	int socketfd;
	std::string domainSocketPath;
	struct sockaddr_un domainSocket;

	void loadConfig();

public:

	DomainSocketUtils();
	~DomainSocketUtils();

	void killNodeJsServer(const char* killcmd);
	void writeData(const char* Data);
};

#endif
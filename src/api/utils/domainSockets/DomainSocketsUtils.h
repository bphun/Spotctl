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


class DomainSocketUtils {

private:

	const char* killServerCmd = "pkill -f 'node webApiInterface.js'";

	int socketfd;
	std::string domainSocketPath;
	struct sockaddr_un domainSocket;

	void loadConfig();
	void connectToServer();

public:

	DomainSocketUtils();
	~DomainSocketUtils();

	void killNodeJsServer();
	void writeData(const char* Data);
};

#endif
#include "DomainSocketsUtils.h"

DomainSocketUtils::DomainSocketUtils() {
	loadConfig();

	socketfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (socketfd < 0) {
		throw SocketException("Could not create socket\n");
		exit(1);
	}

	domainSocket.sun_family = AF_UNIX;
	strcpy(domainSocket.sun_path, domainSocketPath.c_str());

	if (connect(socketfd, (struct sockaddr *) &domainSocket, sizeof(domainSocket)) < 0) {
		throw SocketException("Could not connect to web api interface server");
		exit(1);
	}

	printf("connected socket to host at%s\n", domainSocket.sun_path);
}

DomainSocketUtils::~DomainSocketUtils() {
	close(socketfd);
	unlink(domainSocketPath.c_str());
	killNodeJsServer();
}

void DomainSocketUtils::loadConfig() {
	std::ifstream configFile;
	configFile.open("src/api/utils/domainSockets/sharedConfig.txt");

	if (!configFile) {
		fprintf(stderr, "Could not open domain socket config file\n");
		exit(1);
	}

	configFile >> domainSocketPath;

	configFile.close();
}

void DomainSocketUtils::writeData(const char* data) {
	if (write(socketfd, data, strlen(data)) < 0) {
		throw SocketException("Could not write data to host\n");
		exit(1);
	}
}

void DomainSocketUtils::killNodeJsServer() {
	std::shared_ptr<FILE> pipe(popen(killServerCmd, "r"), pclose);
	if (!pipe) {
		throw SocketException("Unable to kill web api server");
		exit(1);
	}
}



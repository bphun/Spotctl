#include "DomainSocketsUtils.h"

/*
 * Initializes a domain socket bound to the path designated in ./sharedConfig.txt.
 * If no connection is established, a SocketException is thrown and an exit code is set
 */
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
}

/*
 * Destructs the domain socket by closing the sockets connection, unbinding the path and killing the Node.JS server
 */
DomainSocketUtils::~DomainSocketUtils() {
	close(socketfd);
	unlink(domainSocketPath.c_str());
	killNodeJsServer("pkill -f 'node webApiInterface.js'");
}

/*
 * Reads ./sharedConfig.txt to determine the path that socket should bind to
 */
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

/*
 * Triggers a socket write method which writes 'data' to 'domainSocketPath'.
 * If an error occurs while writing data to the path,  a SocketException is thrown
 * 
 * @param data The data that will be written to 'domainSocketPath'
 */
void DomainSocketUtils::writeData(const char* data) {
	if (write(socketfd, data, strlen(data)) < 0) {
		throw SocketException("Could not write data to host\n");
		exit(1);
	}
}

/*
 * Kills the Node.JS server will the designated command
 * If an error is written to stderr during the kill process, a SocketException is thrown
 *
 * @param killCmd The command used to kill the Node.JS backend
 */
void DomainSocketUtils::killNodeJsServer(const char* killCmd) {
	std::shared_ptr<FILE> pipe(popen(killCmd, "r"), pclose);
	if (!pipe) {
		throw SocketException("Unable to kill web api server");
		exit(1);
	}
}



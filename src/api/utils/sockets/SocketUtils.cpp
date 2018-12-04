#include "SocketUtils.h"

/**
 * Initializes a Unix socket bound to localhost and the designated port
 * 
 * @param port The port that the data will be sent through
 *
 * @throws SocketException 
 */
SocketUtils::SocketUtils(int port) {
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		throw SocketException("Could not initialize socket");
		exit(1);
	}

	memset(&sock, '0', sizeof(sock));

	sock.sin_family = AF_INET;
	sock.sin_port = htons(port);

	sock.sin_addr.s_addr = inet_addr("127.0.0.1");
}

/**
 * Initializes a Unix socket bound to a host and port
 *
 * @param hostname The host that the socket wil be bound to
 * @param port Port that the socket will be bound to
 *
 * @throws SocketException
 */
SocketUtils::SocketUtils(const char* hostname, int port) {
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		throw SocketException("Could not initialize socket");
		exit(1);
	}

	memset(&sock, '0', sizeof(sock));

	sock.sin_family = AF_INET;
	sock.sin_port = htons(port);

	sock.sin_addr.s_addr = inet_addr(hostnameToIP(hostname));
}

/**
 * Closes the socket connection
 */
SocketUtils::~SocketUtils() {
	socketfd = -1;
	close(socketfd);
}


/**
 * Resolves a hostname to an IPv4 address
 * 
 * @param hostname Hostname that will be resolved to an IPv4 address
 * 
 * @return An IPv4 representation of the hostname
 *
 * @throws SocketException
 * 
 */
char* SocketUtils::hostnameToIP(const char* hostname) {
	struct hostent *he;
	struct in_addr **addr_list;

	if ((he = gethostbyname(hostname)) == NULL) {
		throw SocketException("Error resolving host to IPv4 address");
	}

	addr_list = (struct in_addr **) he->h_addr_list;

	for(int i = 0; addr_list[i] != NULL; i++) {
		return inet_ntoa(*addr_list[i]);
	}
}

/**
 * Connects the socket to the host set in the constructor
 *
 * @throws SocketException
 */
void SocketUtils::connectToHost() {
	if (connect(socketfd, (struct sockaddr*)&sock, sizeof(sock)) < 0) {
		throw SocketException("Could not connect to host");
		exit(1);
	}
}

/**
 * Sends data over the socket to the host
 * 
 * @param data data that will be sent to the host
 */
void SocketUtils::sendData(const char* data) {
	send(socketfd, data, strlen(data), 0);
}

/**
 * Reads data sent from the host over the socket
 * 
 * @param size Byte size of the data being received
 * @param buffer Buffer for data from the socket to be written to
 */
void SocketUtils::receiveData(int size, char buffer[size]) {
	read(socketfd, buffer, size);
}

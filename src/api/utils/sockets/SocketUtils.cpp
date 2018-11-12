#include "SocketUtils.h"

SocketUtils::SocketUtils() {
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		throw SocketException("Could not initialize socket");
		exit(1);
	}

	memset(&sock, '0', sizeof(sock));

	sock.sin_family = AF_INET;
	sock.sin_port = htons(3000);

	// sock.sin_addr.s_addr = inet_addr("104.154.127.64");
	sock.sin_addr.s_addr = inet_addr("127.0.0.1");
}

SocketUtils::SocketUtils(const char* hostname, int port) {
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		throw SocketException("Could not initialize socket");
		exit(1);
	}

	memset(&sock, '0', sizeof(sock));

	sock.sin_family = AF_INET;
	sock.sin_port = htons(port);

	// sock.sin_addr.s_addr = inet_addr("104.154.127.64");
	sock.sin_addr.s_addr = inet_addr(hostnameToIP(hostname));
}

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

void SocketUtils::connectToHost() {
	if (connect(socketfd, (struct sockaddr*)&sock, sizeof(sock)) < 0) {
		throw SocketException("Could not connect to host");
		exit(1);
	}
}

void SocketUtils::sendData(const char* data) {
	send(socketfd, data, strlen(data), 0);
}

void SocketUtils::receiveData(const char* data, int size, char buffer[size]) {
	read(socketfd, buffer, size);
}

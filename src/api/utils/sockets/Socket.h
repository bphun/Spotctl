#ifndef SOCKET_H
#define SOCKET_H

// #include <sio_client.h>
// #include <internal/sio_packet.h>

#include <thread>
#include <mutex>
#include <string>
#include <sio_client.h>
#include <condition_variable>

#include "ConnectionListener.h"
#include "../exceptions/SocketException.h"

/**
* Socket.IO Socket wrapper
*
* A wrapper for the Socket.IO socket library
* 
*/

class Socket {

private:

	sio::client sock;
	sio::socket::ptr currentSocket; 

	ConnectionListener listener;

	std::string hostIP;
	std::string connectionPortNumber;
	std::string serverResponseMessage;

	bool dataAvailable;

	void bindEvents();

public:

	Socket(std::string hostIP, std::string connectionPortNumber);

	// ~Socket();

	// void closeSocketConnection();
	void emit(std::string label, std::string msg);
	void emit(std::string label);

	std::string getReceivedData();

};

#endif
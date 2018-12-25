#include "ConnectionListener.h"

/**
 * Initilaizes the connection listener  
 */
ConnectionListener::ConnectionListener(sio::client &h)/*:handler(h)*/ {
	connect_finish = false;
	// socketBusy = false;
}

/**
 * Called when the Socket.IO socket connects to a server. Also notifies the condition variable
 * that a connection has been established.
 */
void ConnectionListener::onConnected() {
	_lock.lock();
	// socketBusy = true;
	connect_finish = true;
	_cond.notify_all();
	_lock.unlock();
}

/**
 * Called by Socket.IO when the socket closes.
 * 
 * @param reason Integer representign the close reason
 */
void ConnectionListener::onClose(sio::client::close_reason const& reason) {
	if (reason == sio::client::close_reason_normal) {
		std::cout << "Socket closed by user" << std::endl;
	} else if (reason == sio::client::close_reason_drop) {
		std::cout << "Socket connection was dropped" << std::endl;
	}
}

/**
 * Called when a socket operation fails 
 */
void ConnectionListener::onFail() {
	std::cout << "Socket failed" << std::endl;
	exit(0);
}

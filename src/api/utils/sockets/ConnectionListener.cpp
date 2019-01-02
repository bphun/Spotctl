#include "ConnectionListener.h"

/**
 * Initilaizes the connection listener  
 */
ConnectionListener::ConnectionListener(sio::client &h) {
	connect_finish = false;
}

/**
 * Called when the Socket.IO socket connects to a server. Also notifies the condition variable
 * that a connection has been established.
 */
void ConnectionListener::onConnected() {
	_lock.lock();
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
		fprintf(stdout, "Socket closed by user\n");
	} else if (reason == sio::client::close_reason_drop) {
		throw SocketException("Socket connection was dropped");
	}
}

/**
 * Called when a socket operation fails 
 */
void ConnectionListener::onFail() {
	throw SocketException("Socket failed");
	exit(0);
}

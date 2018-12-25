#ifndef CONNECTION_LISTENER
#define CONNECTION_LISTENER

#include <mutex>
#include <iostream>
#include <sio_client.h>
#include <condition_variable>

extern std::mutex _lock;
extern std::condition_variable_any _cond;
extern bool connect_finish;
// extern bool socketBusy;

/**
 * A collection of methods that are called by Socket.IO when certain events occur.
 * These events consist of socket connection, socket close, and socket failure.
 */
class ConnectionListener {

	// sio::client &handler;

public:

	ConnectionListener(sio::client &h);
	
	void onConnected();
	void onClose(sio::client::close_reason const& reason);
	void onFail();
};

#endif
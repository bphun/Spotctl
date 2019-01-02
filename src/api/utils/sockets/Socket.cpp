#include "Socket.h"

std::mutex _lock;
std::condition_variable_any _cond;
bool connect_finish;
// bool socketBusy;

/**
 * Creates a Socket.IO socket that connects to the desired host and port.
 * Events specified in the bindEvents() method will also be binded in this process.
 *
 * @param hostIP IP address of the host socket server
 * @param connectionPortNumber Port that the socket server is listening on
 * 
 */
Socket::Socket(std::string hostIP, std::string connectionPortNumber): listener(sock) {
	this->hostIP = hostIP;
	this->connectionPortNumber = connectionPortNumber;
	this->dataAvailable = false;

	sock.set_open_listener(std::bind(&ConnectionListener::onConnected, &listener));
	sock.set_close_listener(std::bind(&ConnectionListener::onClose, &listener, std::placeholders::_1));
	sock.set_fail_listener(std::bind(&ConnectionListener::onFail, &listener));

	sock.connect(hostIP + ":" + connectionPortNumber);

	_lock.lock();
	if (!connect_finish) {
		_cond.wait(_lock);
	}
	_lock.unlock();

	currentSocket = sock.socket();

	bindEvents();
}

/**
 * Binds socket events that are written within the method body
 */
void Socket::bindEvents() {
	currentSocket->on("ServerResponse", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp) {
		_lock.lock();
		serverResponseMessage = data->get_map()["uuid"]->get_string();
		dataAvailable = true;
		_cond.notify_all();
		_lock.unlock();
	})); 
}

/**
 * Emits a message to the connected socket server with the specified label and message
 * 
 * @param label Socket.IO message label
 * @param msg   Contents of the message being sent
 */
void Socket::emit(std::string label, std::string msg) {
	currentSocket->emit(label, msg);
}

/**
 * Emits a message to the Socket.IO server with no label
 * 
 * @param msg Message contents
 */
void Socket::emit(std::string msg) {
	currentSocket->emit(msg);
}

/**
 * Retreives data that was most recently fetched by the socket client
 * 
 * @return String representation of the data received
 */
std::string Socket::getReceivedData() {
	_lock.lock();
	if (!dataAvailable) {
		_cond.wait(_lock);
	}
	_lock.unlock();
	dataAvailable = false;
	
	return serverResponseMessage;
}
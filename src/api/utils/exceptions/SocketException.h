#ifndef Socket_EXCEPTION_H
#define Socket_EXCEPTION_H

#include <exception>

class SocketException: public std::exception {

private:
	std::string _message;

public:
	explicit SocketException(const std::string &message): _message(message) {}

	virtual const char* what() const throw() {
		return _message.c_str();
	}

};

#endif
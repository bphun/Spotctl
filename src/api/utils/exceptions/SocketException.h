#ifndef Socket_EXCEPTION_H
#define Socket_EXCEPTION_H

#include <exception>

/**
 * Socket Exception
 *
 * Thrown when an exception occurs during a socket operation
 * 
 */

class SocketException: public std::exception {

private:
	
	std::string _message;

public:

	/**
	 * Initializes the SocketException with the desired exception message
	 * 
	 * @param message A description of the exception that occured
	 */
	explicit SocketException(const std::string &message): _message(message) {}

	/**
	 * @return A description of the exception that occured
	 */
	virtual const char* what() const throw() {
		return _message.c_str();
	}

};

#endif
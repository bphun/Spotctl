#ifndef CURL_EXCEPTION_H
#define CURL_EXCEPTION_H

#include <exception>

struct CurlException: public std::exception {
private:
	std::string _message;

public:
	explicit CurlException(const std::string &message): _message(message) {}

	virtual const char* what() const throw() {
		return _message.c_str();
	}

};

#endif
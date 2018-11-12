#ifndef CURL_EXCEPTION_H
#define CURL_EXCEPTION_H

#include <exception>

struct CurlException: public std::exception {
private:
	std::string _message;

	void generateErrorMessage(std::string &message, int errorCode) {
		switch (errorCode) {
			case 7:
			message = "Could not connect to host";
			break;
			default:
			message = "Unknown error code";
			break;
		}
	}
	
	void generateErrorMessage(std::string &message, int errorCode, bool isKeyServerRequest) {
		switch (errorCode) {
			case 7:
			message = "Could not connect to key server";
			break;
			default:
			message = "Unknown error code";
			break;
		}
	}

public:
	explicit CurlException(int errorCode) {
		generateErrorMessage(_message, errorCode, false);
	}
	explicit CurlException(int errorCode, bool isKeyServerRequest) {
		generateErrorMessage(_message, errorCode, isKeyServerRequest);
	}
	explicit CurlException(const std::string &message): _message(message) {}

	virtual const char* what() const throw() {
		return _message.c_str();
	}

};

#endif
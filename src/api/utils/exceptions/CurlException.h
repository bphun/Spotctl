#ifndef CURL_EXCEPTION_H
#define CURL_EXCEPTION_H

#include <exception>

/**
 * Curl Exception
 *
 * Thrown when an exception occurs when executing a CURL request in CurlUtilities
 * 
 */

struct CurlException: public std::exception {

private:

	std::string _message;

	/**
	 * Parses a CURL error code to generate a description of the exception that occured
	 * 
	 * @param errorCode The CURL error code
	 * @param message A description of the exception that will be set once the errorCode has been parsed 
	 */
	void generateErrorMessage(int errorCode, std::string &message) {
		switch (errorCode) {
			case 7:
			message = "Could not connect to host";
			break;
			default:
			message = "Received unknown error code" + std::to_string(errorCode);
			break;
		}
	}
	
	/**
	 * Parses a CURL error code to generate a description of the exception that occured
	 * 
	 * @param errorCode The CURL error code
	 * @param message A description of the exception that will be set once the errorCode has been parsed
	 * @param isKeyServerRequest Flag used to generate error messages specific to the remote key file server
	 */
	void generateErrorMessage(int errorCode, std::string &message, bool isKeyServerRequest) {
		switch (errorCode) {
			case 3:
			message = "Host URL net specified";
			break;
			case 7:
			message = "Could not connect to key server";
			break;
			case 51:
			message = "Could not verify authenticity of host's certificates";
			break;
			case 52:
			message = "An internal server error occured";
			break;
			default:
			message = "Received unknown error code " + std::to_string(errorCode);
			break;
		}
	}

public:

	/**
	 * Initializes the Curl Exception relative to the provided errorCode
	 * 
	 * @param errorCode a CURL error code that is given by libcurl when an exception occurs
	 */
	explicit CurlException(int errorCode) {
		generateErrorMessage(errorCode, _message);
	}

	/**
	 * Initializes the Curl Exception relative to the provided errorCode
	 * 
	 * @param errorCode a CURL error code that is given by libcurl when an exception occurs
	 * @param isKeyServerRequest Flag used to generate error messages specific to the remote key file server
	 */
	explicit CurlException(int errorCode, bool isKeyServerRequest) {
		generateErrorMessage(errorCode, _message, isKeyServerRequest);
	}

	/**
	 * Initializes the Curl Exception relative to the provided errorCode
	 * 
	 * @param message A description of the exception that occured
	 */
	explicit CurlException(const std::string &message): _message(message) {}

	/**
	 * @return A description of the exception that occured
	 */
	virtual const char* what() const throw() {
		return _message.c_str();
	}

};

#endif
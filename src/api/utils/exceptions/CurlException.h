#ifndef CURL_EXCEPTION_H
#define CURL_EXCEPTION_H

#include "../json.h"
/**
 * Curl Exception
 *
 * Thrown when an exception occurs when executing a CURL request in CurlUtilities
 * 
 */
struct CurlException: public std::exception {

private:
	std::string _message;

	void generateErrorMessage(int statusCode, std::string errorMessageBuffer, std::string& message) {
		switch (statusCode) {
			case 400:
				message = "Bad Request.";
				break;					
			case 401:
				message = "Unauthorized. Authentication is required or has failed.";
				break;
			case 403:
				message = "You do not have the required permissions to access this resource.";
				break;
			case 404:
				message = "Request resource could not be found.";
				break;
			case 405:
				message = "The utilized request method is not permitted is not permitted for this request.";
				break;
			case 406:
				message = "The requested resource is capable of generating only content not acceptable according to the Accept headers sent in the request.";
				break;
			case 407:
				message = "The client must first authenticate itself with the proxy.";
				break;
			case 408:
				message = "The server timed out while waiting for the request.";
				break;
			case 409:
				message = "Request could not be processed because of conflict in the current state of the resource.";
				break;
			case 410:
				message = "Resource requested is no longer available and will not be available again.";
				break;
			case 411:
				message = "The request did not specify the length of its content, which is required by the requested resource.";
				break;
			case 412:
				message = "The server does not meet one of the preconditions that the requester put on the request.";
				break;
			case 413:
				message = "The request is larger than the server is willing or able to process.";
				break;
			case 414:
				message = "The URI provided was too long for the server to process.";
				break;
			case 415:
				message = "The request entity has a media type which the server or resource does not support";
				break;
			case 416:
				message = "The client has asked for a portion of the file, but the server cannot supply that portion.";
				break;
			case 417:
				message = "The server cannot meet the requirements of the Expect request-header field.";
				break;
			case 418:
				message = "I'm a teapot";
				break;
			case 421:
				message = "The request was directed at a server that is not able to produce a response.";
				break;
			case 422:
				message = "The request was well-formed but was unable to be followed due to semantic errors.";
				break;
			case 423:
				message = "The resource that is being accessed is locked.";
				break;
			case 424:
				message = "The request failed because it depended on another request and that request failed";
				break;
			case 426:
				message = "The client should switch to a different protocol such as TLS/1.0, given in the Upgrade header field.";
				break;
			case 428:
				message = "The origin server requires the request to be conditional.";
				break;
			case 429:
				message = "The user has sent too many requests in a given amount of time.";
				break;
			case 431:
				message = "The server is unwilling to process the request because either an individual header field, or all the header fields collectively, are too large.";
				break;
			case 451:
				message = "A server operator has received a legal demand to deny access to a resource or to a set of resources that includes the requested resource.";
				break;
			case 500:
				message = "Internal server error.";
				break;
			case 501:
				message = "The server either does not recognize the request method, or it lacks the ability to fulfil the request.";
				break;
			case 502:
				message = "The server was acting as a gateway or proxy and received an invalid response from the upstream server.";
				break;
			case 503:
				message = "The server is currently unavailable (because it is overloaded or down for maintenance). Try again later.";
				break;
			case 504:
				message = "The server was acting as a gateway or proxy and did not receive a timely response from the upstream server.";
				break;
			case 505:
				message = "The server does not support the HTTP protocol version used in the request.";
				break;
			case 506:
				message = "Transparent content negotiation for the request results in a circular reference.";
				break;
			case 507:
				message = "The server is unable to store the representation needed to complete the request.";
				break;
			case 508:
				message = "The server detected an infinite loop while processing the request";
				break;
			case 510:
				message = "Further extensions to the request are required for the server to fulfil it.";
				break;
			case 511:
				message = "The client needs to authenticate to gain network access.";
				break;
		}

		if (!errorMessageBuffer.empty()) {
			nlohmann::json errorJson = nlohmann::json::parse(errorMessageBuffer);
			message += errorJson["error"]["message"].dump();
		}
	}

public:

	explicit CurlException(int statusCode, std::string errorMessageBuffer) {
		generateErrorMessage(statusCode, errorMessageBuffer, _message);
	}

	explicit CurlException(int statusCode) {
		generateErrorMessage(statusCode, "", _message);
	}

	explicit CurlException(std::string errorMessageBuffer) {
		_message = errorMessageBuffer;
	}

	/**
	 * @return A description of the exception that occured
	 */
	virtual const char* what() const throw() {
		return _message.c_str();
	}
};

#endif
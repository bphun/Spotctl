#ifndef SPOTIFY_EXCEPTION_H
#define SPOTIFY_EXCEPTION_H

#include <exception>

/**
 * Spotify Exception
 *
 * Thrown when an exception occurs while making a request to the Spotify Web API
 * 
 */

struct SpotifyException: public std::exception {
	
private:
	
	std::string _message;

public:

	/**
	 * Initializes the SotifyException with the desired exception message
	 * 
	 * @param message A description of the exception that occured
	 */
	explicit SpotifyException(const std::string &message): _message(message) {}

	/**
	 * @return A description of the exception that occured
	 */
	virtual const char* what() const throw() {
		return _message.c_str();
	}

};

#endif
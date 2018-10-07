#ifndef SPOTIFY_EXCEPTION_H
#define SPOTIFY_EXCEPTION_H

#include <exception>

struct SpotifyException: public std::exception {
private:
	std::string _message;

public:
	explicit SpotifyException(const std::string &message): _message(message) {}

	virtual const char* what() const throw() {
		return _message.c_str();
	}

};

#endif
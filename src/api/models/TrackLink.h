#ifndef TRACK_LINK_H
#define TRACK_LINK_H

#include <map>
#include <string>

class TrackLink {

private:

	std::map<std::string, std::string> externalUrls;
	std::string href;
	std::string id;
	std::string type;
	std::string uri;

public:

	std::map<std::string, std::string> getExternalURLS();
	std::string getHref();
	std::string getID();
	std::string getType();
	std::string getURI();

};

#endif
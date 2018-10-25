#ifndef TRACK_LINK_H
#define TRACK_LINK_H

#include <map>
#include <string>

#include "../utils/json/json.hpp"

class TrackLink {

private:

	std::string id;	
	std::string uri;
	std::string href;
	std::string type;
	std::map<std::string, std::string> externalUrls;

public:

	TrackLink(nlohmann::json trackLinkJson);

	std::string getID();
	std::string getURI();
	std::string getHref();
	std::string getType();
	std::map<std::string, std::string> getExternalURLS();

};

#endif
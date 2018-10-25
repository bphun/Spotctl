#include "TrackLink.h"

TrackLink::TrackLink(nlohmann::json trackLinkJson) {
	
	id = trackLinkJson["id"];
	uri = trackLinkJson["uri"];
	href = trackLinkJson["href"];
	type = trackLinkJson["type"];

	for (auto it = trackLinkJson["external_urls"].begin(); it != trackLinkJson["external_urls"].end(); it++) {
		externalUrls[it.key()] = it.value();
	}
}

std::string TrackLink::getID() {
	return this->id;
}

std::string TrackLink::getURI() {
	return this->uri;
}

std::string TrackLink::getHref() {
	return this->href;
}

std::string TrackLink::getType() {
	return this->type;
}

std::map<std::string, std::string> TrackLink::getExternalURLS() {
	return this->externalUrls;
}
#include "TrackLink.h"

/**
 * Initializes the track link object with data in the given JSON
 *
 * @param trackLinkJson JSON containing track link data
 */
TrackLink::TrackLink(nlohmann::json trackLinkJson) {
	
	id = trackLinkJson["id"];
	uri = trackLinkJson["uri"];
	href = trackLinkJson["href"];
	type = trackLinkJson["type"];

	for (auto it = trackLinkJson["external_urls"].begin(); it != trackLinkJson["external_urls"].end(); it++) {
		externalUrls[it.key()] = it.value();
	}
}

/**
 *
 */
std::string TrackLink::getid() {
	return this->id;
}

/**
 * 
 */
std::string TrackLink::getURI() {
	return this->uri;
}

/**
 * 
 */
std::string TrackLink::getHref() {
	return this->href;
}

/**
 * 
 */
std::string TrackLink::getType() {
	return this->type;
}

/**
 * 
 */
std::map<std::string, std::string> TrackLink::getExternalURLS() {
	return this->externalUrls;
}
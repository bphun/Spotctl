#include "Track.h"

Track::Track() = default;

Track::Track(nlohmann::json trackJson) {
	// std::cout << trackJson.dump(4) << std::endl;

	explicitSong = trackJson["explicit"];
	// playable = trackJson["is_playable"]
	durationMs = trackJson["duration_ms"];
	discNumber = trackJson["disc_number"];
	trackNumber = trackJson["track_number"];
	id = trackJson["id"];
	uri = trackJson["uri"];
	href = trackJson["href"];
	name = trackJson["name"];
	type = trackJson["type"];
	if (!trackJson["preview_url"].is_null()) {
		previewUrl = trackJson["preview_url"];
	}
	// linkedFrom = TrackLink()
	for (nlohmann::json artist : trackJson["artists"]) {
		artists.push_back(Artist(artist));
	}

	for (std::string market : trackJson["available_markets"]) {
		availableMarkets.push_back(market);
	}
	for (auto it = trackJson["external_urls"].begin(); it != trackJson["external_urls"].end(); it++) {
		externalUrls[it.key()] = it.value();
	}
}

bool Track::isExplicit() {
	return this->explicitSong;
}

bool Track::isPlayable() {
	return this->playable;
}

int Track::getDiscNumber() {
	return this->discNumber;
}

int Track::getDurationMs() {
	return this->durationMs;
}

int Track::getTrackNumber() {
	return this->trackNumber;
}

std::string Track::getID() {
	return this->id;
}

std::string Track::getURI() {
	return this->uri;
}

std::string Track::getHref() {
	return this->href;
}

std::string Track::getName() {
	return this->name;
}

std::string Track::getType() {
	return this->type;
}

std::string Track::getPreviewUrl() {
	return this->previewUrl;
}

// TrackLink Track::getLinkedFrom() {
// 	return this->getLinkedFrom
// }

std::vector<Artist> Track::getArtists() {
	return this->artists;
}

std::vector<std::string> Track::getAvailableMarkets() {
	return this->availableMarkets;
}

std::map<std::string, std::string> Track::getExternalUrls() {
	return externalUrls;
}

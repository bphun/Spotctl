#include "Track.h"

Track::Track() = default;

/**
 * Initializes the track with the data in the provided JSON
 * 
 * @param trackJson JSON containing track data
 */
Track::Track(nlohmann::json trackJson) {

	explicitSong = trackJson["explicit"];
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

/**
 * @return Whether or not this track is explicit
 */
bool Track::isExplicit() {
	return this->explicitSong;
}

/**
 * @return Whether or not the track is currently playable
 */
bool Track::isPlayable() {
	return this->playable;
}

/**
 * @return The disc number (usually 1 unless the album consists of more than one disc)
 */
int Track::getDiscNumber() {
	return this->discNumber;
}

/**
 * @return The length of the track in milliseconds
 */
int Track::getDurationMs() {
	return this->durationMs;
}

/**
 * @return The track's position in an album
 */
int Track::getTrackNumber() {
	return this->trackNumber;
}

/**
 * @return The track's spotify ID
 */
std::string Track::getid() {
	return this->id;
}

/**
 * @return The Tracks Spotify URI
 */
std::string Track::getURI() {
	return this->uri;
}

/**
 * @return The track's href
 */
std::string Track::getHref() {
	return this->href;
}

/**
 * @return The track's name
 */
std::string Track::getName() {
	return this->name;
}

/**
 * @return A generic Spotify track (Always "track")
 */
std::string Track::getType() {
	return this->type;
}

/**
 * @return URL where a preview of the track can be played
 */
std::string Track::getPreviewUrl() {
	return this->previewUrl;
}

/**
 * @return Vector of artists that worked on this track
 */
std::vector<Artist> Track::getArtists() {
	return this->artists;
}

/**
 * @return Vector of markets where this track is available
 */
std::vector<std::string> Track::getAvailableMarkets() {
	return this->availableMarkets;
}

/**
 * @return Map of known external Urls where this track is available
 */
std::map<std::string, std::string> Track::getExternalUrls() {
	return externalUrls;
}

#include "Album.h"

Album::Album() = default;

/**
 * Initializes an album object with data received from spotify's album json
 *
 * @param albumJson JSON containing album data
 */
Album::Album(nlohmann::json albumJson) {
	for (nlohmann::json artistJson : albumJson["artists"]) {
		artists.push_back(Artist(artistJson));
	}
	for (std::string market : albumJson["available_markets"]) {
		availableMarkets.push_back(market);
	}
	for (nlohmann::json copyrightJson : albumJson["copyrights"]) {
		copyrights.push_back(Copyright(copyrightJson));
	}
	for (std::string genre : albumJson["genres"]) {
		genres.push_back(genre);
	}

	this->href = albumJson["href"];
	this->name = albumJson["name"];
	if (!albumJson["popularity"].is_null()) {
		this->popularity = albumJson["popularity"];
	}
	this->releaseDate = albumJson["release_date"];
	this->tracks = Pager<Track>(albumJson["tracks"]);
}

Album::~Album() = default;

/**
 * @return int representing Album's popularity
 */
int Album::getPopularity() {
	return this->popularity;
}

/**
 * @return Album's name
 */
std::string Album::getName() {
	return this->name;
}

/**
 * @return Album's href
 */
std::string Album::getHref() {
	return this->href;
}

/**
 * @return Album's release date
 */
std::string Album::getReleaseDate() {
	return this->releaseDate;
}

/**
 * @return Vector of artists that collaborated on the album
 */
std::vector<Artist> Album::getArtists() {
	return this->artists;
}

/**
 * @return Pager object wiht tracks included in the album
 */
Pager<Track> Album::getTracks() {
	return this->tracks;
}

/**
 * @return Vector of strings containing album's genres
 */
std::vector<std::string> Album::getGenres() {
	return this->genres;
}

/**
 * @return Vector of strings that represent countries where the album is available
 */
std::vector<std::string> Album::getAvailableMarkets() {
	return this->availableMarkets;
}

/**
 * @return Vector of copyrights associated with this album
 */
std::vector<Copyright> Album::getCopyrights() {
	return this->copyrights;
}

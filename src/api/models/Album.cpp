#include "Album.h"

Album::Album() = default;

Album::Album(nlohmann::json albumJson) {
	// std::cout << albumJson.dump(4) << std::endl;

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

int Album::getPopularity() {
	return this->popularity;
}

std::string Album::getName() {
	return this->name;
}

std::string Album::getHref() {
	return this->href;
}

std::string Album::getReleaseDate() {
	return this->releaseDate;
}

std::vector<Artist> Album::getArtists() {
	return this->artists;
}

Pager<Track> Album::getTracks() {
	return this->tracks;
}

std::vector<std::string> Album::getGenres() {
	return this->genres;
}

std::vector<std::string> Album::getAvailableMarkets() {
	return this->availableMarkets;
}

std::vector<Copyright> Album::getCopyrights() {
	return this->copyrights;
}
#include "Album.h"

Album::Album(nlohmann::json albumJson) {
	for (nlohmann::json artistJson : albumJson["artists"]) {
		artists.push_back(Artist(artistJson));
	}
	for (std::string market : albumJson["available_markets"]) {
		available_markets.push_back(market);
	}
	for (nlohmann::json copyrightJson : albumJson["copyrights"]) {
		copyrights.push_back(Copyright(copyrightJson));
	}
	for (std::string genre : albumJson["genres"]) {
		genres.push_back(genre);
	}

	this->href = albumJson["href"];
	this->name = albumJson["name"];
	this->popularity = albumJson["popularity"];
	this->releaseDate = albumJson["release_date"];
	this->tracks = Pager<Track>(albumJson("tracks"));
}

Album::~Album() {
	this->popularity = 0;
	this->name.clear();
	this->releaseDate.clear();
	this->artists.clear();
	this->tracks.clear();
	this->genres.clear();
	this->copyrights->clear();
}

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

std::vector<Track> Album::getTracks() {
	return this->tracks;
}

std::vector<std::string> Album::getGenres() {
	return this->genres;
}

std::vector<std::string> Album::getAvailableMarkets() {
	return availableMarkets;
}

std::vector<Copyright> Album::getCopyrights() {
	return this->copyrights;
}
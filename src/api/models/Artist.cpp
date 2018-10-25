#include "Artist.h"

Artist::Artist(nlohmann::json artistJson) {
	// this->popularity = artistJson["popularity"];
	this->id = artistJson["id"];
	this->name = artistJson["name"];
	this->followers = Followers(artistJson["followers"]);
	for (std::string genre : genres) {
		genres.push_back(genre);
	}
}

// int Artist::getPopularity() {
// 	return this->popularity;
// }

std::string Artist::getID() {
	return this->id;
}

std::string Artist::getName() {
	return this->name;
}

Followers Artist::getFollowers() {
	return this->followers;
}

std::vector<std::string> Artist::getGenres() {
	return this->genres;
}

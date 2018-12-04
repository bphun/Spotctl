#include "Artist.h"

/**
 * Initializes the object with the given JSON
 *
 * @param artistJson JSON containing artist data
 */
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

/**
 * @return Artist's spotify identifcation number
 */
std::string Artist::getid() {
	return this->id;
}

/**
 * @return Artist's name
 */
std::string Artist::getName() {
	return this->name;
}

/**
 * This is usually empty, Spotify does not yet return a artist's followers 
 *
 * @return Followers object containing an artist's followers
 */
Followers Artist::getFollowers() {
	return this->followers;
}

/**
 * @return Vector containing genres associated with the artist 
 */
std::vector<std::string> Artist::getGenres() {
	return this->genres;
}

#ifndef ARTIST_H
#define ARTIST_H

#include "Followers.h"

/**
 *
 * Artist object
 *
 * Stores data received from Spotify when an artist is requested 
 *
 */

class Artist {

private:

	// int popularity;
	std::string id;
	std::string name;
	Followers followers;
	std::vector<std::string> genres;

public:

	Artist(nlohmann::json artistJson);

	// int getPopularity();
	std::string getid();
	std::string getName();
	Followers getFollowers();
	std::vector<std::string> getGenres();

};

#endif
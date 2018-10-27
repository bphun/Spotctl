#ifndef ARTIST_H
#define ARTIST_H

#include <string>
#include <vector>

#include "Followers.h"

#include "../utils/json.h"

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
	std::string getID();
	std::string getName();
	Followers getFollowers();
	std::vector<std::string> getGenres();

};

#endif
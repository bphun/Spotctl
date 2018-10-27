#ifndef ALBUM_H
#define ALBUM_H

#include <vector>
#include <string>

#include "Pager.h"
#include "Track.h"
#include "Artist.h"
#include "Copyright.h"

#include "../utils/json.h"

class Album {

private:

	int popularity;
	std::string name;
	std::string href;
	std::string releaseDate;
	Pager<Track> tracks;
	std::vector<Artist> artists;
	std::vector<std::string> genres;
	std::vector<std::string> availableMarkets;
	std::vector<Copyright> copyrights;

public:
	
	Album();
	Album(nlohmann::json albumJson);
	~Album();

	int getPopularity();
	std::string getName();
	std::string getHref();
	std::string getReleaseDate();
	Pager<Track> getTracks();
	std::vector<Artist> getArtists();
	std::vector<std::string> getGenres();
	std::vector<std::string> getAvailableMarkets();
	std::vector<Copyright> getCopyrights();
};

#endif
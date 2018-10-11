#ifndef TRACK_H
#define TRACK_H

#include <map>
#include <vector>
#include <string>

#include "User.h"
#include "Artist.h"
#include "TrackLink.h"

class Track {

private:

	std::vector<Artist> artists;
	std::vector<std::string> availableMarkets;

	std::map<std::string, std::string> externalUrls;

	int discNumber;
	int durationS;
	int trackNumber;

	bool isExplicit;
	bool isPlayable;

	TrackLink linkedFrom;

	std::string href;
	std::string id;
	std::string name;
	std::string previewUrl;
	std::string type;
	std::string uri;

public:
	

};

#endif
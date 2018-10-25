#ifndef SAVED_TRACK_H
#define SAVED_TRACK_H

#include <string>

#include "Track.h"

#include "../utils/json/json.hpp"

class SavedTrack {

private:

	std::string addedAt;
	Track track;

public:

	SavedTrack(nlohmann::json trackJson);

	std::string getAddedAt();
	Track getTrack();

};

#endif
#ifndef SAVED_TRACK_H
#define SAVED_TRACK_H

#include <string>

#include "Track.h"

#include "../utils/json.h"

/**
 * Saved Track Object
 *
 * Stores a track with the date and time it was added
 *
 */

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
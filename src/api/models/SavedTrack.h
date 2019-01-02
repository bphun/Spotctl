#ifndef SAVED_TRACK_H
#define SAVED_TRACK_H

#include "Track.h"

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
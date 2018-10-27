#ifndef PLAYLIST_TRACK_H
#define PLAYLIST_TRACK_H

#include <string>

#include "User.h"
#include "Track.h"

#include "../utils/json.h"

class PlaylistTrack {

private:

	bool local;
	std::string addedAt;
	Track track;
	UserPublic addedBy;

public:

	PlaylistTrack(nlohmann::json trackJson);

	bool isLocal();
	std::string getAddedAt();
	Track getTrack();
	UserPublic getAddedBy();

};

#endif
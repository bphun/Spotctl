#ifndef PLAYLIST_TRACK_H
#define PLAYLIST_TRACK_H

#include <string>

#include "User.h"
#include "Track.h"
#include "../utils/json.h"

class PlaylistTrack {

private:

	std::string addedAt;
	UserPublic addedBy;
	bool isLocal;
	Track track;

public:

	PlaylistTrack(nlohmann::json trackJson);

	std::string getAddedAt();
	User getAddedBy();
	bool isLocal();
	std::shared_ptr<Track> getTrack();

};

#endif
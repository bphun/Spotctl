#ifndef PLAYLIST_TRACK_H
#define PLAYLIST_TRACK_H

#include "Track.h"

/**
 * Playlist Track Object
 *
 * Stores a track that is associated with a playlist
 *
 */

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
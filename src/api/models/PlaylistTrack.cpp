#include "PlaylistTrack.h"

/**
 * Initializes the playlist track object with data provided in the JSON
 *
 * @param trackJson JSON that contains track data
 */
PlaylistTrack::PlaylistTrack(nlohmann::json trackJson) {
	addedAt = trackJson["added_at"];
	addedBy = UserPublic(trackJson["added_by"]);
	local = trackJson["is_local"];
	track = Track(trackJson["track"]);
}

/**
 * @return Date and time that the track was added at
 */
std::string PlaylistTrack::getAddedAt() {
	return this->addedAt;
}

/**
 * @return The user that added the track to the playlist
 */
UserPublic PlaylistTrack::getAddedBy() {
	return this->addedBy;
}

/**
 * @return whether or not the playlist is stored locally
 */
bool PlaylistTrack::isLocal() {
	return this->local;
}

/**
 * @return returns the associated track
 */
Track PlaylistTrack::getTrack() {
	return this->track;
}

#include "SavedTrack.h"

/**
 * Initializes the saved track with data in the given JSON
 *
 * @param trackJson JSON containing the saved track's data
 */
SavedTrack::SavedTrack(nlohmann::json trackJson) {
	addedAt = trackJson["added_at"];
	track = Track(trackJson["track"]);
}

/**
 * @return The date and time the track was saved
 */
std::string SavedTrack::getAddedAt() {
	return this->addedAt;
}

/**
 * @return The associated track
 */
Track SavedTrack::getTrack() {
	return this->track;
}

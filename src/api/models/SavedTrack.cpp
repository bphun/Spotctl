#include "SavedTrack.h"

SavedTrack::SavedTrack(nlohmann::json trackJson) {
	addedAt = trackJson["added_at"];
	track = Track(trackJson["track"]);
}

std::string SavedTrack::getAddedAt() {
	return this->addedAt;
}

Track SavedTrack::getTrack() {
	return this->track;
}

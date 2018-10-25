#include "PlaylistTrack.h"

PlaylistTrack::PlaylistTrack(nlohmann::json trackJson) {
	addedAt = trackJson["added_at"];
	addedBy = UserPublic(trackJson["added_by"]);
	local = trackJson["is_local"];
	track = Track(trackJson["track"]);
}

std::string PlaylistTrack::getAddedAt() {
	return this->addedAt;
}

UserPublic PlaylistTrack::getAddedBy() {
	return this->addedBy;
}

bool PlaylistTrack::isLocal() {
	return this->local;
}

Track PlaylistTrack::getTrack() {
	return this->track;
}

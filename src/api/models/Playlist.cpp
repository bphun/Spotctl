#include "Playlist.h"

Playlist::Playlist(nlohmann::json playlistJson) {
	owner = UserPublic(playlistJson["owner"]);
	publicPlaylist = playlistJson["public"];
	collaborative = playlistJson["collaborative"];
	id = playlistJson["id"];
	uri = playlistJson["uri"];
	type = playlistJson["type"];
	if (!playlistJson["description"].is_null()) {
		description = playlistJson["description"];
	}
	name = playlistJson["name"];
	href = playlistJson["href"];
	snapshotId = playlistJson["snapshot_id"];
	tracks = Pager<PlaylistTrack>(playlistJson["tracks"]);

	for (auto it = playlistJson["external_urls"].begin(); it != playlistJson["external_urls"].end(); ++it) {
		externalUrls[it.key()] = it.value();
	}

	followers = Followers(playlistJson["followers"]);
}

bool Playlist::isPublic() {
	return this->publicPlaylist;
}

bool Playlist::isCollaborative() {
	return this->collaborative;
}

std::string Playlist::getID() {
	return this->id;
}

std::string Playlist::getURI() {
	return this->uri;
}

std::string Playlist::getHref() {
	return this->href;
}

std::string Playlist::getName() {
	return this->name;
}

std::string Playlist::getDescription() {
	return this->description;
}

std::string Playlist::getType() {
	return this->type;
}

UserPublic Playlist::getOwner() {
	return this->owner;
}

std::string Playlist::getSnapshotID() {
	return this->snapshotId;
}

Pager<PlaylistTrack> Playlist::getTracks() {
	return this->tracks;
}

std::map<std::string, std::string> Playlist::getExternalUrls() {
	return this->externalUrls;
}

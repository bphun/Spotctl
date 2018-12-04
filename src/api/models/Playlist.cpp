#include "Playlist.h"

/**
 * Initializes a playlist object with data in the given JSON
 *
 * @param playlistJson JSON containing playlist data
 */
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

/**
 * @return Whether or not the playlist is public
 */
bool Playlist::isPublic() {
	return this->publicPlaylist;
}

/**
 * @return Boolean that delineates if the playlist is a collaboration
 */
bool Playlist::isCollaborative() {
	return this->collaborative;
}

/**
 * @return Playlist's ID
 */
std::string Playlist::getid() {
	return this->id;
}

/**
 * @return Playlist's Spotify URI
 */
std::string Playlist::getURI() {
	return this->uri;
}

/**
 * @return Playlist's href
 */
std::string Playlist::getHref() {
	return this->href;
}

/**
 * @return Playlist's name
 */
std::string Playlist::getName() {
	return this->name;
}

/**
 * @return A description of the playlist
 */
std::string Playlist::getDescription() {
	return this->description;
}

/**
 * @return general object type (Always "playlist")
 */
std::string Playlist::getType() {
	return this->type;
}

/**
 * @return User who owns the playlist
 */
UserPublic Playlist::getOwner() {
	return this->owner;
}

/**
 * @return Version identifier for the playlist
 */
std::string Playlist::getSnapshotID() {
	return this->snapshotId;
}

/**
 * @return Pager of the playlist's tracks
 */
Pager<PlaylistTrack> Playlist::getTracks() {
	return this->tracks;
}

/**
 * @return Map of known external URL's for this playlist
 */
std::map<std::string, std::string> Playlist::getExternalUrls() {
	return this->externalUrls;
}

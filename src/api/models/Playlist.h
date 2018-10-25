#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <map>
#include <vector>
#include <string>

#include "Pager.h"
#include "Followers.h"
#include "UserPublic.h"
#include "PlaylistTrack.h"

#include "../utils/json/json.hpp"

class Playlist {

private:

	bool collaborative;
	bool publicPlaylist;
	std::string id;
	std::string uri;
	std::string type;
	std::string name;
	std::string href;
	std::string snapshotId;
	std::string description;
	UserPublic owner;
	Followers followers;
	Pager<PlaylistTrack> tracks;
	std::map<std::string, std::string> externalUrls;

public:

	Playlist(nlohmann::json playlistJson);

	bool isCollaborative();
	bool isPublic();
	std::string getID();
	std::string getURI();
	std::string getType();
	std::string getName();
	std::string getHref();
	std::string getSnapshotID();
	std::string getDescription();
	UserPublic getOwner();
	Pager<PlaylistTrack> getTracks();
	std::map<std::string, std::string> getExternalUrls();

};

#endif
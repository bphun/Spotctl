#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <map>
#include <vector>
#include <string>

#include "User.h"
#include "PlaylistTrack.h"
#include "Pager.h"
#include "Followers.h"

class Playlist {

private:

	User owner;
	bool isPublic;
	bool isCollaborative;
	std::string id;
	std::string uri;
	std::string type;
	std::string name;
	std::string href;
	std::string snapshotId;
	Pager<PlaylistTrack> tracks;
	std::map<std::string, std::string> externalUrls;



public:
	bool isPublic();
	bool isCollaborative();
	std::string getID();
	std::string getURI();
	std::string getHref();
	std::string getName();
	std::string getType();
	std::string getOwner();
	std::string getSnapshotID();
	Pager<PlaylistTrack> getTracks();
	std::map<std::string, std::string> getExternalUrls();


};

#endif
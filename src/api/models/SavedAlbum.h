#ifndef SAVED_ALBUM_H
#define SAVED_ALBUM_H

#include <string>

#include "Album.h"

#include "../utils/json/json.hpp"

class SavedAlbum {

private:

	std::string addedAt;
	Album album;

public:

	SavedAlbum(nlohmann::json albumJson);

	std::string getAddedAt();
	Album getAlbum();
	
};


#endif
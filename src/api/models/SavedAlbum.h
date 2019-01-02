#ifndef SAVED_ALBUM_H
#define SAVED_ALBUM_H

#include "Album.h"

/**
 * Saved Album Object
 *
 * This is essentially and Album object but it includes the date that the album was added
 *
 */

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
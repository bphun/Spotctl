#include "SavedAlbum.h"

/**
 * Initializes the saved album
 *
 * @param albumJson JSON containing data pertaining to the saved album
 */
SavedAlbum::SavedAlbum(nlohmann::json albumJson) {
    addedAt = albumJson["added_at"];
    album = Album(albumJson["album"]);
}

/**
 * @return The date and time this album was saved
 */
std::string SavedAlbum::getAddedAt() {
    return addedAt;
}

/**
 * @return the associated album
 */
Album SavedAlbum::getAlbum() {
    return album;
}
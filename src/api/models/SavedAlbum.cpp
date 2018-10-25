#include "SavedAlbum.h"

SavedAlbum::SavedAlbum(nlohmann::json albumJson) {
    addedAt = albumJson["added_at"];
    album = Album(albumJson["album"]);
}

std::string SavedAlbum::getAddedAt() {
    return addedAt;
}

Album SavedAlbum::getAlbum() {
    return album;
}
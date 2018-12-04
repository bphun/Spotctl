#include "UserPublic.h"

UserPublic::UserPublic() = default;

/**
 * Initializes the UserPublic object with data in the given JSON
 */
UserPublic::UserPublic(nlohmann::json userJson) {
	id = userJson["id"];
	uri = userJson["uri"];
	href = userJson["href"];
	type = userJson["type"];
	displayName = userJson["display_name"];
	followers = Followers(userJson["followers"]);
	for (auto it = userJson["external_urls"].begin(); it != userJson["external_urls"].end(); it++) {
		externalUrls[it.key()] = it.value();
	}
}

/**
 * @return The user's ID
 */
std::string UserPublic::getid() {
	return this->id;
}

/**
 * @return The User's URI
 */
std::string UserPublic::getURI() {
	return this->uri;
}

/**
 * @return The User's href
 */
std::string UserPublic::getHref() {
	return this->href;
}

/**
 * @return A general Spotify type. Always "user"
 */
std::string UserPublic::getType() {
	return this->type;
}

/**
 * @return The user's publicly visible name
 */
std::string UserPublic::getDisplayName() {
	return this->displayName;
}

/**
 * @return Followers object containing followers of the user
 */
Followers UserPublic::getFollowers() {
	return this->followers;
}

/**
 * @return Map of known external URL's where the user can be fetched
 */
std::map<std::string, std::string> UserPublic::getExternalUrls() {
	return this->externalUrls;
}


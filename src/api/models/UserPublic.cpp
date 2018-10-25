#include "UserPublic.h"

UserPublic::UserPublic() = default;

UserPublic::UserPublic(nlohmann::json userJson) {
	// std::cout << userJson << std::endl;
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

std::string UserPublic::getID() {
	return this->id;
}

std::string UserPublic::getURI() {
	return this->uri;
}

std::string UserPublic::getHref() {
	return this->href;
}

std::string UserPublic::getType() {
	return this->type;
}

std::string UserPublic::getDisplayName() {
	return this->displayName;
}

Followers UserPublic::getFollowers() {
	return this->followers;
}

std::map<std::string, std::string> UserPublic::getExternalUrls() {
	return this->externalUrls;
}


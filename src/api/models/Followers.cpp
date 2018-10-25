#include "Followers.h"

Followers::Followers() = default;

Followers::Followers(nlohmann::json followersJson) {
	if (!followersJson["href"].is_null()) {
		href = followersJson["href"];
	}

	if (followersJson["total"].is_null()) {
		total = 0;
	} else {
		total = followersJson["total"];
	}
}

int Followers::getTotal() {
	return this->total;
}

std::string Followers::getHref() {
	return this->href;
}

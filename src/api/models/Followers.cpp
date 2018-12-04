#include "Followers.h"

Followers::Followers() = default;

/**
 * Initializes the followers object with data in the given JSON
 *
 * @param followersJson JSON containing the user's or album's followers 
 */
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

/**
 * @return Number of followers
 */
int Followers::getTotal() {
	return this->total;
}

/**
 * @return href linking to the followers
 */
std::string Followers::getHref() {
	return this->href;
}

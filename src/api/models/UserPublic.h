#ifndef USER_PUBLIC_H
#define USER_PUBLIC_H

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "Followers.h"

#include "../utils/json.h"

/**
 * User Public Object
 *
 * Stores information that allows for access of public user data
 *
 */
class UserPublic {

private:

	std::string id;
	std::string uri;
	std::string href;
	std::string type;
	std::string displayName;
	std::map<std::string, std::string> externalUrls;
	Followers followers;

public:

	UserPublic();
	UserPublic(nlohmann::json userJson);

	std::string getid();
	std::string getURI();
	std::string getHref();
	std::string getType();
	std::string getDisplayName();
	std::map<std::string, std::string> getExternalUrls();
	Followers getFollowers();

};

#endif
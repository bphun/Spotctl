#ifndef FOLLOWERS_H
#define FOLLOWERS_H

#include <string>

#include "../utils/json/json.hpp"

class Followers {

private:

	int total;
	std::string href;

public:

	Followers(nlohmann::json followersJson);
	Followers();

	int getTotal();
	std::string getHref();


};

#endif
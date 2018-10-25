#ifndef USER_H
#define USER_H

#include <string>

#include "UserPublic.h"

#include "../utils/json/json.hpp"

class User: public UserPublic {

private:

	std::string email;
	std::string product;
	std::string country;

public:

	User(nlohmann::json userJson);

	std::string getEmail();
	std::string getProduct();
	std::string getCountry();

};

#endif
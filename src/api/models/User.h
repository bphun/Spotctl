#ifndef USER_H
#define USER_H

#include <string>

#include "UserPublic.h"

#include "../utils/json.h"

/**
 *  User Object
 *
 * Stores general data associated with a user
 *
 */

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
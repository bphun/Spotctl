#ifndef USER_H
#define USER_H

#include <string>

#include "../utils/json.h"

class User {

private:

	std::string country;
	std::string email;
	std::string product;

public:

	User(nlohmann::json json);

	std::string getCountry();
	std::string getEmail();
	std::string getProduct();

};

#endif
#include "User.h"

/**
 * Initializes the user object with data in the given object
 *
 * @param userJson JSON containing general user data
 */
User::User(nlohmann::json userJson): UserPublic(userJson) {
	email = userJson["email"];
	country = userJson["country"];
	product = userJson["product"];
}

/**
 * @return The user's email
 */
std::string User::getEmail() {
	return this->email;
}

/**
 * @return The user's account country of origin
 */
std::string User::getCountry() {
	return this->country;
}

/**
 * @return The User's account type. Either "premium" or "free"
 */
std::string User::getProduct() {
	return this->product;
}

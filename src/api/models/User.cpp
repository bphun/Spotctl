#include "User.h"

User::User(nlohmann::json userJson): UserPublic(userJson) {
	email = userJson["email"];
	country = userJson["country"];
	product = userJson["product"];
}

std::string User::getEmail() {
	return this->email;
}

std::string User::getCountry() {
	return this->country;
}

std::string User::getProduct() {
	return this->product;
}

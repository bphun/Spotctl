#include "Copyright.h"

Copyright::Copyright(nlohmann::json copyrightJson) {
	this->type = copyrightJson["type"];
	this->description = copyrightJson["text"];
}

std::string Copyright::getType() {
	return this->type;
}

std::string Copyright::getDescription() {
	return this->description;
}


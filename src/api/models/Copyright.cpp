#include "Copyright.h"

/**
 * Initializes copyright object from a JSON containing copyright data
 *
 * @param copyrightJson JSON containing copyright data
 *
 */
Copyright::Copyright(nlohmann::json copyrightJson) {
	this->type = copyrightJson["type"];
	this->description = copyrightJson["text"];
}

/**
 * @return The copyright's type. (C: copyright), (P: sound recording (performance) copyright)
 */
std::string Copyright::getType() {
	return this->type;
}

/**
 * @return Copyright text
 */
std::string Copyright::getDescription() {
	return this->description;
}


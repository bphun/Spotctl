#ifndef COPYRIGHT_H
#define COPYRIGHT_H

#include "../utils/json.h"

/**
 * A copyright object
 *
 * Stores copyright information that associated with an album or song
 *
 */

class Copyright {

private:

	std::string type;
	std::string description;

public:

	Copyright(nlohmann::json copyrightJson);

	std::string getType();
	std::string getDescription();

};

#endif
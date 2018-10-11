#ifndef COPYRIGHT_H
#define COPYRIGHT_H

#include <string>

#include "../utils/json.h"

class Copyright {

private:

	std::string type;
	std::string description;

public:

	Copyright(nlohmann::json json);
	~Copyright();

	std::string getType();
	std::string getDescription();

};

#endif
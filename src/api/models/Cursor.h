#ifndef CURSOR_H
#define CURSOR_H

#include <string>

#include "../utils/json/json.hpp"

class Cursor {
	
private:

	std::string after;

public:

	Cursor(nlohmann::json cursorJson);

	std::string GetAfter();

};


#endif
#ifndef CURSOR_H
#define CURSOR_H

#include "../utils/json.h"

/**
 * Cursor object
 *
 * Represents the current item
 * Honestly, idk what this is used for
 *
 */

class Cursor {
	
private:

	std::string after;

public:

	Cursor();
	Cursor(nlohmann::json cursorJson);

	std::string GetAfter();

};


#endif
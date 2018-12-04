#include "Cursor.h"

Cursor::Cursor() = default;

/**
 * Initializes the cursor with data provided in the given JSON
 *
 * @param cursorJson JSON containing current cursor data
 */
Cursor::Cursor(nlohmann::json cursorJson) {
    if(!cursorJson["after"].is_null()) {
        after = cursorJson["after"];
    }
}

/**
 * @return The cursor to use as key to find the next page of items
 */
std::string Cursor::GetAfter() {
    return this->after;
}
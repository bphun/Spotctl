#include "Cursor.h"

Cursor::Cursor() = default;

Cursor::Cursor(nlohmann::json cursorJson) {
    if(!cursorJson["after"].is_null()) {
        after = cursorJson["after"];
    }
}

std::string Cursor::GetAfter() {
    return this->after;
}
#ifndef CURSOR_PAGER_H
#define CURSOR_PAGER_H

#include <string>
#include <vector>

#include "Cursor.h"

#include "../utils/json/json.hpp"


template <class T> class CursorPager {

private:

    int limit;
    int total;
    std::string href;
    std::string next;
    Cursor cursors;
    std::vector<T> items;

public:

    CursorPager<T>();
    CursorPager<T>(nlohmann::json pagerJson);

    int getLimit();
    int getTotal();
    std::string getHref();
    std::string getNext();
    Cursor getCursors();
    std::vector<T> getItems();

};

#endif
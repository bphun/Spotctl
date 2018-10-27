#ifndef CURSOR_PAGER_H
#define CURSOR_PAGER_H

#include <string>
#include <vector>

#include "Cursor.h"

#include "../utils/json.h"


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

template<typename T> CursorPager<T>::CursorPager() = default;

template<typename T> CursorPager<T>::CursorPager(nlohmann::json pagerJson) {
    href = pagerJson["href"];
    limit = pagerJson["limit"];
    cursors = Cursor(pagerJson["cursors"]);
    total = pagerJson["total"];
    
    if(!pagerJson["next"].is_null()) {
        next = pagerJson["next"];
    }

    for(nlohmann::json json : pagerJson["items"]) {
        items.push_back(T(json));
    }
}

template<typename T> std::string CursorPager<T>::getHref() {
    return this->href;
}

template<typename T> std::vector<T> CursorPager<T>::getItems() {
    return this->items;
}

template<typename T> int CursorPager<T>::getLimit() {
    return this->limit;
}

template<typename T> std::string CursorPager<T>::getNext() {
    return this->next;
}

template<typename T> Cursor CursorPager<T>::getCursors() {
    return this->cursors;
}

template<typename T> int CursorPager<T>::getTotal() {
    return this->total;
}

#endif
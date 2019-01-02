#ifndef CURSOR_PAGER_H
#define CURSOR_PAGER_H

#include "Cursor.h"

/**
 * Cursor Pager object
 *
 * Stores list of items encased in a Cursor pager object
 *
 */

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

/**
 * Initializes the cursor pager with the provided JSON
 *
 * @param pagerJson JSON containing the pager's data
 */
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

/**
 * @return Cursor Pager's href
 */
template<typename T> std::string CursorPager<T>::getHref() {
    return this->href;
}

/**
 * @return Vector containing the pager's data
 */
template<typename T> std::vector<T> CursorPager<T>::getItems() {
    return this->items;
}

/**
 * @return Maximum number of items in this pager
 */
template<typename T> int CursorPager<T>::getLimit() {
    return this->limit;
}

/**
 * @return The next item in the pager
 */
template<typename T> std::string CursorPager<T>::getNext() {
    return this->next;
}

/**
 * @return Cursors in the pager
 */
template<typename T> Cursor CursorPager<T>::getCursors() {
    return this->cursors;
}

/**
 * @return Total number of items in the pager
 */
template<typename T> int CursorPager<T>::getTotal() {
    return this->total;
}

#endif
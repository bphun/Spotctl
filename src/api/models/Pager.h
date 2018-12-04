#ifndef PAGER_H
#define PAGER_H

#include <string>
#include <vector>

#include "../utils/json.h"

/**
 * Pager Object
 *
 * This is essentially a list of a desired type but with some aids
 *
 */

template <class T> class Pager {

private:

	int limit;
	int total;
	int offset;
	std::string href;
	std::string next;
	std::string previous;
	std::vector<T> items;

public:

	Pager<T>();
	Pager<T>(nlohmann::json pagerJson);

	int getLimit();
	int getTotal();
	int getOffset();
	std::string getHref();
	std::string getNext();
	std::string getPrevious();
	std::vector<T> getItems();

};

template <typename T> Pager<T>::Pager() = default;

template <typename T> Pager<T>::Pager(nlohmann::json pagerJson) {
	if (!pagerJson["href"].is_null()) {
		href = pagerJson["href"];
	}
	for (nlohmann::json json : pagerJson["items"]) {
		items.push_back(T(json));
	}
	if (!pagerJson["limit"].is_null()) {
		limit = pagerJson["limit"];
	}
	if (!pagerJson["next"].is_null()) {
		next = pagerJson["next"];
	}
	if (!pagerJson["offset"].is_null()) {
		offset = pagerJson["offset"];
	}
	if (!pagerJson["previous"].is_null()) {
		previous = pagerJson["previous"];
	}
	if (!pagerJson["total"].is_null()) {
		total = pagerJson["total"];
	}
}

/**
 * @return Pager's href
 */
template <typename T> std::string Pager<T>::getHref() {
	return href;
}

/**
 * @return Vector of items in the pager
 */
template <typename T> std::vector<T> Pager<T>::getItems() {
	return items;
}

/**
 * @return Maximum number of item that are in this pager
 */
template <typename T> int Pager<T>::getLimit() {
	return limit;
}

/**
 * @return Next item in the pager
 */
template <typename T> std::string Pager<T>::getNext() {
	return next;
}

/**
 * @return Pager's offset
 */
template <typename T> int Pager<T>::getOffset() {
	return offset;
}

/**
 * @return previous item in the pager
 */
template <typename T> std::string Pager<T>::getPrevious() {
	return previous;
}

/**
 * @return total number of items in the pager
 */
template <typename T> int Pager<T>::getTotal() {
	return total;
}

#endif
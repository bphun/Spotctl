#ifndef PAGER_H
#define PAGER_H

#include <string>
#include <vector>

#include "../utils/json.h"

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

template <typename T> std::string Pager<T>::getHref() {
	return href;
}

template <typename T> std::vector<T> Pager<T>::getItems() {
	return items;
}

template <typename T> int Pager<T>::getLimit() {
	return limit;
}

template <typename T> std::string Pager<T>::getNext() {
	return next;
}

template <typename T> int Pager<T>::getOffset() {
	return offset;
}

template <typename T> std::string Pager<T>::getPrevious() {
	return previous;
}

template <typename T> int Pager<T>::getTotal() {
	return total;
}

#endif
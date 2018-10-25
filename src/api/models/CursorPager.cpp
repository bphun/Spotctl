#include "CursorPager.h"

template<class T> CursorPager<T>::CursorPager() = default;

template<class T> CursorPager<T>::CursorPager(nlohmann::json pagerJson) {
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

template<class T> std::string CursorPager<T>::getHref() {
	return this->href;
}

template<class T> std::vector<T> CursorPager<T>::getItems() {
	return this->items;
}

template<class T> int CursorPager<T>::getLimit() {
	return this->limit;
}

template<class T> std::string CursorPager<T>::getNext() {
	return this->next;
}

template<class T> Cursor CursorPager<T>::getCursors() {
	return this->cursors;
}

template<class T> int CursorPager<T>::getTotal() {
	return this->total;
}

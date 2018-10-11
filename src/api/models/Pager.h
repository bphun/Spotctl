#ifndef PAGER_H
#define PAGER_H

#include <string>
#include <vector>

#include "../utils/json.h"

template <class T> class Pager {

private:

	int total;
	int limit;
	int offset;
	std::string href;
	std::string next;
	std::string previous;
	std::vector<T> items;

public:

	Pager<T>(nlohmann::json json);

	std::string getHref();
	std::string getNext();
	std::string getPrevious();
	std::vector<T> getItems();

};

#endif
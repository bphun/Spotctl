#ifndef CONTEXT_H
#define CONTEXT_H

#include "../utils/json.h"

class Context {

private:
	std::string uri;
	std::string href;
	std::string type;
	std::map<std::string, std::string> externalUrls;

public:

	Context();
	Context(nlohmann::json contextJson);

	std::string getUri();
	std::string getHref();
	std::string getType();
	std::map<std::string, std::string> getExternalUrls();

};


#endif
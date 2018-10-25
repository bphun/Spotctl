#include "Context.h"

Context::Context() = default;

Context::Context(nlohmann::json contextJson) {
	uri = contextJson["uri"];
	href = contextJson["href"];
	type = contextJson["type"];

	for (auto it = contextJson["external_urls"].begin(); it != contextJson["external_urls"].end(); it++) {
		externalUrls[it.key()] = it.value();
	}
}

std::string Context::getUri() {
	return this->uri;
}

std::string Context::getHref() {
	return this->href;
}

std::map<std::string, std::string> Context::getExternalUrls() {
	return this->externalUrls;
}

std::string Context::getType() {
	return this->type;
}

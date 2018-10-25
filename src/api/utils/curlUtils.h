#ifndef CURL_UTILS_H
#define CURL_UTILS_H

#include <curl/curl.h>

// #include <nlohmann/json.hpp>

#include "json/json.hpp"
#include "SpotifyException.h"
#include "CurlException.h"

class CurlUtils {
private:
	std::string replaceAll(std::string& str, const std::string from, const std::string to);

public:
	static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);

	nlohmann::json runRequest(std::string request, std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body);

	nlohmann::json GET(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body = "");
	nlohmann::json POST(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body = "");
	nlohmann::json PUT(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body = "");
	nlohmann::json DELETE(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body = "");
};

#endif
#ifndef CURL_UTILS_H
#define CURL_UTILS_H

#include <curl/curl.h>

#include "../exceptions/CurlException.h"

/**
 * Curl Utilities
 *
 * A utility to facilitate CURL requests to various hosts. This is primaril used for Spotify Web API request but
 * it can be used to for requests to any host you would like.
 *
 */

class CurlUtils {
	
private:

	std::string replaceAll(std::string& str, const std::string from, const std::string to);

	#ifdef LOCALTEST
	const char* caCertPath = "cert/selfCA_local.key";
	#else
	const char* caCertPath = "cert/selfCA.key";
	#endif

	void addKeyServerConfig(CURL* curl);

	bool isKeyServerRequest = false;

public:

	static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);

	nlohmann::json runRequest(std::string request, std::string endpoint, std::map<std::string, std::string> options = std::map<std::string, std::string>(), std::string authorizationToken = "", std::string body = "", std::string baseURL = "https://api.spotify.com");

	nlohmann::json GET(std::string endpoint, std::map<std::string, std::string> options = std::map<std::string, std::string>(), std::string authorizationToken = "", std::string body = "");
	nlohmann::json GET(std::string endpoint, std::string baseURL, std::map<std::string, std::string> options = std::map<std::string, std::string>(), std::string authorizationToken = "", std::string body = "");

	nlohmann::json POST(std::string endpoint, std::string baseURL, std::string body);
	nlohmann::json POST(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body = "");
	nlohmann::json POST(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body, std::string baseURL);
	
	nlohmann::json PUT(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body = "");
	
	nlohmann::json DELETE(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body = "");

};

#endif
#include "CurlUtils.h"

size_t CurlUtils::writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string CurlUtils::replaceAll(std::string& str, const std::string from, const std::string to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

void CurlUtils::addKeyServerConfig(CURL* curl) {
	const char* caCertPath = "cert/selfCA.pem";
	// std::string certKeyPath = "cert/selfCA.key";

	// curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");
	// curl_easy_setopt(curl, CURLOPT_SSLCERT, certFilePath);

	// curl_easy_setopt(curl, CURLOPT_SSLKEYTYPE, "key");
	// curl_easy_setopt(curl, CURLOPT_SSLKEY, certKeyPath);

	// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(curl, CURLOPT_CAINFO, caCertPath);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
}

nlohmann::json CurlUtils::runRequest(std::string request, std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body, std::string baseURL) {
	CURL* curl;

	curl = curl_easy_init();
	if (!curl) {
		throw CurlException("Error: Could not initialize cURL");
	}

	std::string url = baseURL + endpoint;

	if (baseURL != "https://api.spotify.com") {
		addKeyServerConfig(curl);
	}

	if (!options.empty()) {
		url += "?";
		for (auto option : options) {
			url += option.first + "=" + option.second + "&";
		}
		replaceAll(url, " ", "%20");
	}

	std::string readBuffer;

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.c_str());

	if (!authorizationToken.empty()) {
		std::string authHeader = "Authorization: Bearer " + authorizationToken;
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, authHeader.c_str());

		// if (request == "POST") {
			// std::string contentTypeHeader = "Content-Type: application/json";
			// std::string contentLengthHeader = "Content-Length: 0";
			// headers = curl_slist_append(headers, contentTypeHeader.c_str());
			// headers = curl_slist_append(headers, contentLengthHeader.c_str());
		// }

		if (request == "PUT") {
			std::string contentLengthHeader = "Content-Length: 0";
			headers = curl_slist_append(headers, contentLengthHeader.c_str());
		}

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	}

	if (!body.empty()) {
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
	}

		if (!postData.empty()) {
		// printf("asdfadfasdfasdfasdfad\n");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
	}

	int responseCode = curl_easy_perform(curl);
	if (responseCode != CURLE_OK) {
		throw CurlException("Error: " + std::to_string(responseCode));
	}

	long statusCode = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);
	if (statusCode < 200 || statusCode > 204) {
		throw SpotifyException("Error: \n" + readBuffer);
	}

	curl_easy_cleanup(curl);

	if (readBuffer.empty()) {
		return nlohmann::json();
	}

	return nlohmann::json::parse(readBuffer);
}

void CurlUtils::setPostData(std::string postData) {
	this->postData = postData;
}

void CurlUtils::clearPostData() {
	this->postData = "";
}

nlohmann::json CurlUtils::GET(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body) {
	return runRequest("GET", endpoint, options, authorizationToken, body, endpoint.find("/static/") == std::string::npos ? "https://api.spotify.com" : "https://localhost:3000");
}

nlohmann::json CurlUtils::POST(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body) {
	return runRequest("POST", endpoint, options, authorizationToken, body);
}

nlohmann::json CurlUtils::PUT(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body) {
	return runRequest("PUT", endpoint, options, authorizationToken, body);
}

nlohmann::json CurlUtils::DELETE(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body) {
	return runRequest("DELETE", endpoint, options, authorizationToken, body);
}

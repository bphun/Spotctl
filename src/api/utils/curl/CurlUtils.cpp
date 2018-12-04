#include "CurlUtils.h"

size_t CurlUtils::writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

/**
 * Replaces all instances of a string to a specified string
 *
 * @param str String that will be operated on
 * @param from String that will be removed and replaced with desired string
 * @param to String replaced with replaced
 * @return A New string with instances of the undesired pattern are replaced with the specified string
 *
 */
std::string CurlUtils::replaceAll(std::string& str, const std::string from, const std::string to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

/**
 * Configures a CURL object for communication with the client's remote key file server
 *
 * @param curl A CURL object which needs to have options inserted to allow for communcations with the remote key file server
 *
 */
void CurlUtils::addKeyServerConfig(CURL* curl) {
	#ifdef DEBUG
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	#endif
	curl_easy_setopt(curl, CURLOPT_CAINFO, caCertPath);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

	isKeyServerRequest = true;
}

/**
 * Runs either GET, POST, PUT, or DELETE request with the specifed endpoint, options, URL, and JSON body (usually for POST requests)
 *
 * @param request Type of CURL request (GET, POST, PUT, DELETE)
 * @param endpoint endpoint of the specified URL where the desired data is located
 * @param options The desired options that you would like to send to the host. Defaults to an empty map
 * @param authorizationToken The token used by Spotify to authenticate a request. Defaults to an empty string
 * @param body Data that is sent to the host. Defaults an empty string
 * @param baseURL URL (Excluding endpoint) that the request will be made to. Defaults to "https://api.spotify.com"
 *
 * @return A JSON containing data returned from the request
 *
 * @throws CurlException
 * @throws SpotifyException
 * 
 */
nlohmann::json CurlUtils::runRequest(std::string request, std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body, std::string baseURL) {
	CURL* curl;

	curl = curl_easy_init();
	if (!curl) {
		throw CurlException("Could not initialize cURL");
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

		if (request == "PUT") {
			std::string contentLengthHeader = "Content-Length: 0";
			headers = curl_slist_append(headers, contentLengthHeader.c_str());
		}

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	}

	if (!body.empty()) {
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
	}

	int responseCode = curl_easy_perform(curl);
	if (responseCode != CURLE_OK) {
		throw CurlException(responseCode, isKeyServerRequest);
	}

	long statusCode = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);
	if (statusCode < 200 || statusCode > 204) {
		throw SpotifyException("\n" + readBuffer);
	}

	curl_easy_cleanup(curl);

	if (readBuffer.empty()) {
		return nlohmann::json();
	}

	return nlohmann::json::parse(readBuffer);
}

/**
 * Runs a GET request to the Spotify Web API with the specified endpoint
 *
 * @param endpoint The endpoint that the request is made to
 * @param options The desired options that you would like to send to the host. Defaults to an empty map
 * @param authorizationToken The token used by Spotify to authenticate a request. Defaults to an empty string
 * @param body Data that is sent to the host. Defaults an empty string
 *
 * @return A JSON containing data returned from the request
 *
 */
nlohmann::json CurlUtils::GET(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body) {
	return runRequest("GET", endpoint, options, authorizationToken, body/*, endpoint.find("/static/") == std::string::npos ? "https://api.spotify.com" : "https://localhost:3000"*/);
}

/**
 * Runs a GET request to the Spotify Web API, or any desired http server, with the specified endpoint
 *
 * @param endpoint The endpoint that the request is made to
 * @param baseURL The URL that the request is made to
 * @param options The desired options that you would like to send to the host. Defaults to an empty map
 * @param authorizationToken The token used by Spotify to authenticate a request. Defaults to an empty string
 * @param body Data that is sent to the host. Defaults an empty string
 *
 * @return A JSON containing data returned from the request
 *
 */
nlohmann::json CurlUtils::GET(std::string endpoint, std::string baseURL, std::map<std::string, std::string> options, std::string authorizationToken, std::string body) {
	return runRequest("GET", endpoint, options, authorizationToken, body, baseURL);
}

/**
 * Runs a POST request to the Spotify Web API, or any desired http server, with the specified endpoint and body
 *
 * @param endpoint The endpoint that the request is made to
 * @param baseURL URL (Excluding endpoint) that the request will be made to 
 * @param body Data that is sent to the host. Defaults an empty string
 *
 * @return A JSON containing data returned from the request
 *
 */
nlohmann::json CurlUtils::POST(std::string endpoint, std::string baseURL, std::string body) {
	return runRequest("POST", endpoint, std::map<std::string, std::string>(), "", body, baseURL);
}

/**
 * Runs a POST request to the Spotify Web API, or any desired http server, with the specified endpoint and body
 *
 * @param endpoint The endpoint that the request is made to
 * @param options The desired options that you would like to send to the host. Defaults to an empty map
 * @param authorizationToken The token used by Spotify to authenticate a request. Defaults to an empty string
 * @param body Data that is sent to the host. Defaults an empty string
 *
 * @return A JSON containing data returned from the request
 *
 */
nlohmann::json CurlUtils::POST(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body) {
	return runRequest("POST", endpoint, options, authorizationToken, body);
}

/**
 * Runs a POST request to the Spotify Web API, or any desired http server, with the specified endpoint and body
 *
 * @param endpoint The endpoint that the request is made to
 * @param options The desired options that you would like to send to the host
 * @param authorizationToken The token used by Spotify to authenticate a request
 * @param body Data that is sent to the host. Defaults an empty string
 * @param baseURL URL (Excluding endpoint) that the request will be made to
 *
 * @return A JSON containing data returned from the request
 *
 */
nlohmann::json CurlUtils::POST(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body, std::string baseURL) {
	return runRequest("POST", endpoint, options, authorizationToken, body, baseURL);
}

/**
 * Runs a PUT request to the Spotify Web API with the specified endpoint and body
 *
 * @param endpoint The endpoint that the request is made to
 * @param options The desired options that you would like to send to the host
 * @param authorizationToken The token used by Spotify to authenticate a request
 * @param body Data that is sent to the host. Defaults an empty string
 *
 * @return A JSON containing data returned from the request
 *
 */
nlohmann::json CurlUtils::PUT(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body) {
	return runRequest("PUT", endpoint, options, authorizationToken, body);
}

/**
 * Runs a DELETE request to the Spotify Web API with the specified endpoint
 *
 * @param endpoint The endpoint that the request is made to
 * @param options The desired options that you would like to send to the host
 * @param authorizationToken The token used by Spotify to authenticate a request
 * @param body Data that is sent to the host. Defaults an empty string
 *
 * @return A JSON containing data returned from the request
 *
 */
nlohmann::json CurlUtils::DELETE(std::string endpoint, std::map<std::string, std::string> options, std::string authorizationToken, std::string body) {
	return runRequest("DELETE", endpoint, options, authorizationToken, body);
}

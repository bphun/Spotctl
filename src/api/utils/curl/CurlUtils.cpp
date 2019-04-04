#include "CurlUtils.h"

CurlUtils::CurlUtils() {
	curl = curl_easy_init();
}

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
	#ifdef CLIENT_DEBUG
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	#endif

	if (!curl) {
		throw CurlException("Could not initialize cURL");
	}

	std::string url = baseURL + endpoint;

	if (!options.empty()) {
		url += "?";
		for (auto option : options) {
			url += option.first + "=" + option.second + "&";
		}
		replaceAll(url, " ", "%20");
	}
	// printf("%s\n", url.c_str());

	std::string readBuffer;

	if (request == "POST") {
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
	}

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	// curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.c_str());

	if (!authorizationToken.empty()) {
		std::string authHeader = "Authorization: Bearer " + authorizationToken;
		headers = curl_slist_append(headers, authHeader.c_str());

		std::string contentLengthHeader = "Content-Length: 0";
		headers = curl_slist_append(headers, contentLengthHeader.c_str());

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	}

	if (!body.empty()) {
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
	}

	// delete headers;
	
	int responseCode = curl_easy_perform(curl);
	if (responseCode != CURLE_OK) {
		curl = curl_easy_init();
		throw CurlException(responseCode);
	}

	long statusCode = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);	
	// printf("%ld\n", statusCode);
	if (statusCode < 200 || statusCode > 204) {
		curl = curl_easy_init();
		// printf("%ld\n", statusCode);
		throw CurlException(statusCode, readBuffer);
	}

	curl_easy_cleanup(curl);
	if (readBuffer.empty()) {
		curl = curl_easy_init();
		return nlohmann::json();
	}

	isKeyServerRequest = false;
	curl = curl_easy_init();
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

/**
 * Adds a header to the current instance of cURL, which will then be cleared once 
 * the cURL request is executed.
 * 
 * @param headerName Name of the header that will be inserted into the upcoming cURL request
 * @param headerValue Value of the header that will be inserted into the upcoming cURL request.
 */
void CurlUtils::addHeader(std::string headerName, std::string headerValue) {
	std::string header = headerName + ": " + headerValue;
	headers = curl_slist_append(headers, header.c_str());

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
}
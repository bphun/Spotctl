#include "SpotifyAPI.h"

SpotifyAPI::SpotifyAPI() {
	this->clientID = readFileAt("src/api/vars/id.txt");
	this->clientSecret = readFileAt("src/api/vars/secret.txt");
	this->authorizationCode = readFileAt("src/api/vars/authorizationCode.txt");

	CURL* curl;
	curl = curl_easy_init();

	if(!curl) {
		std::cerr << "Could not initiate cURL" << std::endl;
		return;
	}

	requestAccessToken(curl);
	// authorizeUser(curl);

	curl_global_init(CURL_GLOBAL_ALL);

	CurlUtils curlUtils;
	
	options_t options;
	nlohmann::json albumJSON = curlUtils.GET("/v1/me", options, accessToken);
	std::cout << albumJSON.dump() << std::endl;
}

std::string SpotifyAPI::readFileAt(std::string path) {
	std::ifstream file;
	std::string str;

	file.open(path);
	if (!file) {
		printf("Error opening file\n");
		exit(-1);
	}

	file >> str;

	file.close();
	return str;
}

void SpotifyAPI::requestAccessToken(CURL* curl) {

	std::string writeBuffer;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlUtils::writeCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &writeBuffer);

	curl_easy_setopt(curl, CURLOPT_URL, "https://accounts.spotify.com/api/token");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);  // Can't authenticate the certificate, so disable authentication.
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
    std::string postData = "grant_type=authorization_code&code=" + authorizationCode+ "&client_id=" + clientID + "&client_secret=" + clientSecret + "&redirect_uri=https://bphun.github.io";
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

    int responseCode = curl_easy_perform(curl);
    if (responseCode != CURLE_OK) {
    	throw CurlException("Error: \n" + std::to_string(responseCode));
    }
    curl_easy_cleanup(curl);

    nlohmann::json json = nlohmann::json::parse(writeBuffer);

   	// if (json["error"] != "") {
   	// 	const std::string err = json["error"];
   	// 	throw SpotifyException(err);
   	// }

    this->accessToken = json["access_token"];
    this->refreshToken = json["refresh_token"];

    // std::cout << json << std::endl;
}

void SpotifyAPI::authorizeUser(CURL* curl) {

}

bool SpotifyAPI::authenticateUser(char email[], char password[]) {
	return true;
}

void SpotifyAPI::fetchUserPlaylists(std::vector<std::string> &playlists) {
	playlists.push_back("asf");
	playlists.push_back("asf");
	playlists.push_back("asf");
	playlists.push_back("asf");
	playlists.push_back("asf");
	playlists.push_back("asf");
	playlists.push_back("asf");
	playlists.push_back("asf");
	playlists.push_back("asf");
	playlists.push_back("asf");
	playlists.push_back("asdfasdf");
}

// void SpotifyAPI::fetchUserPlaylists(char playlists[2][4]) {
// 	strcpy(playlists[0], "adgq");
// 	strcpy(playlists[1], "abcd");
// }


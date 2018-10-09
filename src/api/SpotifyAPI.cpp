#include "SpotifyAPI.h"

SpotifyAPI::SpotifyAPI() {
	loadConfig();

	// printf("ClientID: %s\nRefresh Token: %s", clientID.c_str(), refreshToken.c_str());

	curl_global_init(CURL_GLOBAL_ALL);


	CurlUtils curlUtils;

	options_t options;
	printf("refreshToken: %s\n", refreshToken.c_str());
	nlohmann::json albumJSON = curlUtils.GET("/v1/albums/41MnTivkwTO3UUJ8DrqEJJ", options, refreshToken);
}

SpotifyAPI::~SpotifyAPI() {
	
}

void SpotifyAPI::loadConfig() {
	std::ifstream configFile;
	std::string configStr;
	int delimiterIndex;

	configFile.open("dontopen.txt");
	if (!configFile) {
		printf("Error opening file\n");
		exit(-1);
	}

	configFile >> configStr;

	delimiterIndex = configStr.find("|");
	
	this->clientID = configStr.substr(0, delimiterIndex);
	this->refreshToken = configStr.substr(delimiterIndex + 1, configStr.size() - 1);
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


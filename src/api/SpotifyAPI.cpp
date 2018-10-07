#include "SpotifyAPI.h"

SpotifyAPI::SpotifyAPI() {
	loadConfig();
	curl_global_init(CURL_GLOBAL_ALL);

	options_t options;
	nlohmann::json albumJSON = GET("/v1/albums/41MnTivkwTO3UUJ8DrqEJJ", options, refreshToken);
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
	
	clientID = configStr.substr(0, delimiterIndex);
	refreshToken = configStr.substr(delimiterIndex + 1, configStr.size() - 1);
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


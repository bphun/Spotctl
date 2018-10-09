#ifndef SPOTIFY_API_H
#define SPOTIFY_API_H

#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>

#include <curl/curl.h>

#include "utils/json.h"
#include "utils/CurlUtils.h"

typedef std::map<std::string, std::string> options_t;
class SpotifyAPI {

private:

	std::string refreshToken, clientID;

	void loadConfig();

public:

	SpotifyAPI();
	~SpotifyAPI();

	void fetchUserPlaylists(std::vector<std::string> &playlists);
	bool authenticateUser(char email[], char password[]);

};

#endif

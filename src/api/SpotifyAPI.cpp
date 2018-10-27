#include "SpotifyAPI.h"

SpotifyAPI::SpotifyAPI() {				
	curl_global_init(CURL_GLOBAL_ALL);
	
	this->clientID = curlUtils.GET("/static/clientid.json")["id"];
	this->clientSecret = curlUtils.GET("/static/clientsecret.json")["secret"];
																		//-----|
	// this->clientID = readFileAt("src/api/vars/id.txt");             	//     |
	// this->clientSecret = readFileAt("src/api/vars/secret.txt");     	//     |--- This is temporary, will write a server to serve this data
	this->refreshToken = readFileAt("src/api/vars/refreshToken.txt");	//     |
																		//-----|
	if (refreshToken != "") {
		requestTokensWithType("refresh_token");

		// options_t options;
		// this->accessToken = curlUtils.POST("/api/token", options, "", "grant_type=refresh_token&refresh_token=" + refreshToken + "&client_id=" + clientID + "&client_secret=" + clientSecret);
	} else {
		// requestAccessToken("authorization_code");
		// requestAccessToken("refresh_token");
		exit(-1);
	}

	// options_t options;
	// nlohmann::json albumJSON = curlUtils.GET("/v1/me", options, accessToken);
	// std::cout << albumJSON << std::endl;
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

void SpotifyAPI::requestAccessToken(std::string grantType) {
	CURL* curl;
	curl = curl_easy_init();

	if(!curl) {
		throw CurlException("Could not initiate cURL");
	}

	std::string postData;
	if (grantType == "refresh_token") {
		postData = "grant_type=refresh_token&refresh_token=" + refreshToken + "&client_id=" + clientID + "&client_secret=" + clientSecret;
		// curlUtils.setPostData(postData);
		// this->accessToken = curlUtils.POST("/api/token")["access_token"];
		// curlUtils.clearPostData();
	} else {
		postData = "grant_type=authorization_code&code=" + refreshToken + "&client_id=" + clientID + "&client_secret=" + clientSecret;
	}

	std::string writeBuffer;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlUtils::writeCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &writeBuffer);

	curl_easy_setopt(curl, CURLOPT_URL, "https://accounts.spotify.com/api/token");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);  // Can't authenticate the certificate, so disable authentication.
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

    int responseCode = curl_easy_perform(curl);
    if (responseCode != CURLE_OK) {
    	throw CurlException("Error: " + std::to_string(responseCode));
    }
    curl_easy_cleanup(curl);

    nlohmann::json json = nlohmann::json::parse(writeBuffer);

    if (grantType == "refresh_token") {
    	this->accessToken = json["access_token"];
    } 
}

void SpotifyAPI::insertOptions(std::vector<std::string> source, std::string key, options_t &destination) {
	std::stringstream ss;

	for (int i = 0; i < source.size(); i++) {
		if (i != 0) {
			ss << ",";
		}
		ss << source[i];
	}

	destination[key] = ss.str();
}


//	Album 

void SpotifyAPI::saveAlbums(std::vector<std::string> albumIds, options_t options) {
	insertOptions(albumIds, "ids", options);
	curlUtils.PUT("/v1/me/albums", options, accessToken);
}

void SpotifyAPI::removeSavedAlbums(std::vector<std::string> albumIds, options_t options) {
	insertOptions(albumIds, "ids", options);
	curlUtils.DELETE("/v1/me/albums", options, accessToken);
}

bool SpotifyAPI::checkSavedAlbums(std::vector<std::string> albumIds, options_t options) {
	insertOptions(albumIds, "ids", options);
	return curlUtils.GET("/v1/me/albums/contains", options, accessToken)[0];
}

Album SpotifyAPI::fetchAlbum(std::string albumID, options_t options) {
	return Album(curlUtils.GET("/v1/albums/" + albumID, options, accessToken));
}

Pager<Album> SpotifyAPI::fetchNewReleases(options_t options) {
	return Pager<Album>(curlUtils.GET("/v1/browse/new-releases", options, accessToken)["albums"]);
}

Pager<SavedAlbum> SpotifyAPI::fetchSavedAlbums(options_t options) {
	return Pager<SavedAlbum>(curlUtils.GET("/v1/me/albums", options, accessToken));
}

Pager<Track> SpotifyAPI::fetchAlbumTracks(std::string albumID, options_t options) {
	return Pager<Track>(curlUtils.GET("/v1/albums/" + albumID + "/tracks", options, accessToken));
}

Pager<Album> SpotifyAPI::searchAlbums(std::string query, options_t options) {
	options["type"] = "album";
	replaceAll(query, " ", "%20");
	options["q"] = query;
	return Pager<Album>(curlUtils.GET("/v1/search", options, accessToken)["albums"]);
}

Pager<Album> SpotifyAPI::fetchArtistAlbums(std::string artistID, options_t options) {
	return Pager<Album>(curlUtils.GET("/v1/artists/" + artistID + "/albums", options, accessToken));
}

std::vector<Album> SpotifyAPI::fetchAlbums(std::vector<std::string> albumIDs, options_t options) {
	std::vector<Album> albums;
	for (std::string albumID : albumIDs) {
		albums.push_back(fetchAlbum(albumID, options));
	}
	return albums;
}


//	Artist

void SpotifyAPI::followArtist(std::string artistID, options_t options) {
	options["type"] = "artist";
	options["ids"] = artistID;
	curlUtils.PUT("/v1/me/following", options, accessToken);
}

bool SpotifyAPI::checkFollowingArtist(std::string artistID, options_t options) {
	options["type"] = "artist";
	options["ids"] = artistID;
	return curlUtils.GET("/v1/me/following/contains", options, accessToken)[0];
}

Artist SpotifyAPI::fetchArtist(std::string artistID, options_t options) {
	return Artist(curlUtils.GET("/v1/artists/" + artistID, options, accessToken));
}

Pager<Artist> SpotifyAPI::fetchUserTopArtists(options_t options) {
	return Pager<Artist>(curlUtils.GET("/v1/me/top/artists", options, accessToken));
}

Pager<Artist> SpotifyAPI::searchArtists(std::string query, options_t options) {
	options["type"] = "artist";
	options["q"] = query;
	return Pager<Artist>(curlUtils.GET("/v1/search", options, accessToken)["artists"]);
}

std::vector<Artist> SpotifyAPI::fetchArtistRelatedArtists(std::string artistID, options_t options) {
	std::vector<Artist> artists;
	nlohmann::json json = curlUtils.GET("/v1/artists/" + artistID + "/related-artists", options, accessToken);
	for(nlohmann::json artistJson : json["artists"]) {
		artists.push_back(Artist(artistJson));
	}
	return artists;
}

std::vector<Artist> SpotifyAPI::fetchArtists(std::vector<std::string> artistIDs, options_t options) {
	std::vector<Artist> artists;
	for (std::string artistID : artistIDs) {
		artists.push_back(fetchArtist(artistID));
	}
	return artists;
}

std::vector<Track> SpotifyAPI::fetchArtistTopTracks(std::string artistID, std::string country, options_t options) {
	std::vector<Track> tracks;
	options["country"] = country;
	nlohmann::json json = curlUtils.GET("/v1/artists/" + artistID + "/top-tracks", options, accessToken);
	for (nlohmann::json trackJson : json["tracks"]) {
		tracks.push_back(Track(trackJson));
	}
	return tracks;
}


//	Playlist

void SpotifyAPI::editPlaylist(std::string userID, std::string playlistId, options_t options) {
	nlohmann::json bodyJson;
	for (auto option : options) {
		bodyJson[option.first] = option.second;
	}

	curlUtils.PUT("/v1/users/" + userID + "/playlists/" + playlistId, options_t(), accessToken, bodyJson.dump(4));
}

void SpotifyAPI::followPlaylist(std::string ownerID, std::string playlistdID, options_t options) {
	curlUtils.PUT("/v1/users/" + ownerID + "/playlists/" + playlistdID + "/followers", options, accessToken);
}

void SpotifyAPI::unfollowPlaylist(std::string ownerID, std::string playlistdID, options_t options) {
	curlUtils.DELETE("/v1/users/" + ownerID + "/playlists/" + playlistdID + "/followers", options, accessToken);
}

void SpotifyAPI::removeTracksFromPlaylist(std::string userID, std::string playlistId, std::vector<std::string> trackIDs, std::string snapshotID) {
	nlohmann::json bodyJson;
	for (std::string trackID : trackIDs) {
		nlohmann::json uriJson;
		uriJson["uri"] = trackID;
		bodyJson["tracks"].push_back(uriJson);
	}

	if (!snapshotID.empty()) {
		bodyJson["snapshot_id"] = snapshotID;
	}

	curlUtils.DELETE("/v1/users/" + userID + "/playlists/" + playlistId + "/tracks", options_t(), accessToken, bodyJson.dump(4));
}

void SpotifyAPI::addTracksToPlaylist(std::string userID, std::string playlistID, std::vector<std::string> trackUris, options_t options) {
	insertOptions(trackUris, "uris", options);
	curlUtils.POST("/v1/users/" + userID + "/playlists/" + playlistID + "/tracks", options, accessToken);
}

void SpotifyAPI::reorderPlaylistTracks(std::string userID, std::string playlistID, int rangeStart, int insertBefore, options_t options) {
	nlohmann::json bodyJson;
	bodyJson["range_start"] = rangeStart;
	bodyJson["insert_before"] = insertBefore;
	for (auto option : options) {
		bodyJson[option.first] = option.second;
	}

	curlUtils.PUT("/v1/users/" + userID + "/playlists/" + playlistID + "/tracks", options_t(), accessToken, bodyJson.dump(4));
}

void SpotifyAPI::replacePlaylistTracks(std::string userID, std::string playlistID, std::vector<std::string> trackUris, options_t options) {
	insertOptions(trackUris, "uris", options);
	curlUtils.PUT("/v1/users/" + userID + "/playlists/" + playlistID + "/tracks", options, accessToken);
}

bool SpotifyAPI::checkUserFollowingPlaylist(std::string userID, std::string playlistID, std::vector<std::string> userIDs, options_t options) {
	insertOptions(userIDs, "ids", options);
	return curlUtils.GET("/v1/users/" + userID + "/playlists/" + playlistID + "/followers/contains", options, accessToken)[0];
}

Playlist SpotifyAPI::createPlaylist(std::string userID, std::string name, options_t options) {
	nlohmann::json bodyJson;
	bodyJson["name"] = name;
	for (auto option : options) {
		bodyJson[option.first] = option.second;
	}
	return Playlist(curlUtils.POST("/v1/users/" + userID + "/playlists", options_t(), accessToken, bodyJson.dump(4)));
}

Playlist SpotifyAPI::fetchPlaylist(std::string userID, std::string playlistID, options_t options) {
	return Playlist(curlUtils.GET("/v1/users/" + userID + "/playlists/" + playlistID, options, accessToken));
}

Pager<PlaylistTrack> SpotifyAPI::fetchPlaylistTracks(std::string userID, std::string playlistID, options_t options) {
	return Pager<PlaylistTrack>(curlUtils.GET("/v1/users/" + userID + "/playlists/" + playlistID + "/tracks", options, accessToken));
}

Pager<Playlist> SpotifyAPI::fetchUserPlaylists(options_t options) {
	return Pager<Playlist>(curlUtils.GET("/v1/me/playlists", options, accessToken));
}

Pager<Playlist> SpotifyAPI::fetchFeaturedPlaylists(options_t options) {
	return Pager<Playlist>(curlUtils.GET("/v1/browse/featured-playlists", options, accessToken)["playlists"]);
}

Pager<Playlist> SpotifyAPI::searchPlaylists(std::string query, options_t options) {
	options["type"] = "playlist";
	options["q"] = query;
	return Pager<Playlist>(curlUtils.GET("/v1/search", options, accessToken)["playlists"]);
}

Pager<Playlist> SpotifyAPI::fetchUserPlaylists(std::string userID, options_t options) {
	return Pager<Playlist>(curlUtils.GET("/v1/users/" + userID + "/playlists", options, accessToken));
}


//	Tracks

void SpotifyAPI::saveTracks(std::vector<std::string> trackIDs, options_t options) {
	insertOptions(trackIDs, "ids", options);
	curlUtils.PUT("/v1/me/tracks", options, accessToken);
}

void SpotifyAPI::unsaveTracks(std::vector<std::string> trackIDs, options_t options) {
	insertOptions(trackIDs, "ids", options);
	curlUtils.DELETE("/v1/me/tracks", options, accessToken);
}

bool SpotifyAPI::checkSavedTracks(std::vector<std::string> trackIDs, options_t options) {
	insertOptions(trackIDs, "ids", options);
	return curlUtils.GET("/v1/me/tracks/contains", options, accessToken)[0];
}

Track SpotifyAPI::fetchTrack(std::string trackID, options_t options) {
	return Track(curlUtils.GET("/v1/tracks/" + trackID, options, accessToken));
}

Recommendations SpotifyAPI::fetchRecommendations(options_t options) {
	return Recommendations(curlUtils.GET("/v1/recommendations", options, accessToken));
}

CurrentlyPlayingTrack SpotifyAPI::fetchUserCurrentPlayingTrack(options_t options) {

}

Pager<SavedTrack> SpotifyAPI::fetchSavedTracks(options_t options) {
	return Pager<SavedTrack>(curlUtils.GET("/v1/me/tracks", options, accessToken));
}

Pager<Track> SpotifyAPI::fetchUserTopTracks(options_t options) {
	return Pager<Track>(curlUtils.GET("/v1/me/top/tracks", options, accessToken));
}

Pager<Track> SpotifyAPI::searchTracks(std::string query, options_t options) {
	options["type"] = "track";
	options["q"] = query;
	return Pager<Track>(curlUtils.GET("/v1/search", options, accessToken)["tracks"]);
}

std::vector<Track> SpotifyAPI::fetchTracks(std::vector<std::string> trackIDs, options_t options) {
	std::vector<Track> tracks;
	for(std::string trackID : trackIDs) {
		tracks.push_back(fetchTrack(trackID, options));
	}
	return tracks;
}


//	playback

CursorPager<PlayHistory> SpotifyAPI::fetchUserRecentlyPlayed(options_t options) {
	return CursorPager<PlayHistory>(curlUtils.GET("/v1/me/player/recently-played", options, accessToken));
}

CurrentlyPlayingContext SpotifyAPI::fetchUserCurrentPlayback(options_t options) {
	return CurrentlyPlayingContext(curlUtils.GET("/v1/me/player", options, accessToken));
}

std::vector<Device> SpotifyAPI::fetchUserDevices(options_t options) {
	std::vector<Device> devices;
	nlohmann::json devicesJson = curlUtils.GET("/v1/me/player/devices", options, accessToken);
	for (nlohmann::json deviceJson : devicesJson["devices"]) {
		devices.push_back(Device(deviceJson));
	}
	return devices;
}


//	User

void SpotifyAPI::followUser(std::string userID, options_t options) {
	options["type"] = "user";
	options["ids"] = userID;
	curlUtils.PUT("/v1/me/following", options, accessToken);
}

void SpotifyAPI::unfollowUser(std::string userID, options_t options) {
	options["type"] = "user";
	options["ids"] = userID;
	curlUtils.DELETE("/v1/me/following", options, accessToken);
}

bool SpotifyAPI::checkFollowingUser(std::string userID, options_t options) {
	options["type"] = "user";
	options["ids"] = userID;
	return curlUtils.GET("/v1/me/following/contains", options, accessToken)[0];
}

User SpotifyAPI::fetchUser(options_t options) {
	return User(curlUtils.GET("/v1/me", options, accessToken));
}


//	Stream Control

void SpotifyAPI::pause(options_t options) {
	curlUtils.PUT("/v1/me/player/pause", options, accessToken);
}

void SpotifyAPI::play(options_t options) {
	curlUtils.PUT("/v1/me/player/play", options, accessToken);
}

void SpotifyAPI::skipToNext(options_t options) {
	curlUtils.POST("/v1/me/player/next", options, accessToken);
}

void SpotifyAPI::skipToPrevious(options_t options) {
	curlUtils.POST("/v1/me/player/previous", options, accessToken);
}

void SpotifyAPI::toggleShuffle(bool state, options_t options) {
	options["state"] = state;
	curlUtils.PUT("/v1/me/player/shuffle", options, accessToken);
}

void SpotifyAPI::setRepeat(std::string state, options_t options) {
	options["state"] = state;
	curlUtils.PUT("/v1/me/player/repeat", options, accessToken);
}

void SpotifyAPI::setVolume(int volumePercent, options_t options) {
	options["volume_percent"] = volumePercent;
	curlUtils.PUT("/v1/me/player/volume", options, accessToken);
}

void SpotifyAPI::transferUserPlayback(std::string deviceId, options_t options) {
	// options[]
	// curlUtils.PUT("/v1/me/player", options, accessToken);
}

std::string SpotifyAPI::replaceAll(std::string& str, const std::string from, const std::string to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}


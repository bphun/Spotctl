#include "SpotifyAPI.h"

/**
 * Initializes the Spotify API and prepares it for requests to the Web API.
 * Connects to remote server to fetch the client ID and secret.
 */
SpotifyAPI::SpotifyAPI() {				
	curl_global_init(CURL_GLOBAL_ALL);
	
	this->clientID = curlUtils.GET("/static/clientid.json", backendURL)["client_id"];
	this->clientSecret = curlUtils.GET("/static/clientsecret.json", backendURL)["client_secret"];
	
	this->refreshToken = readFileAt("src/api/vars/refreshToken.txt");

	if (refreshToken != "") {
		requestAccessToken();
	} else {
		// requestAccessToken("authorization_code");
		requestRefreshToken();
		requestAccessToken();
	}

	std::string postData = "user=" + fetchUser().getid();
	curlUtils.POST("/api/logging", backendURL, postData);
}

/**
 * Initializes the Spotify API and prepares it for requests to the Web API
 *
 * @param clientID Client ID given to you when you create an application in the Spotify developer portal
 * @param clientSecret Client secret given to you when you create an application in the Spotify developer portal
 */
SpotifyAPI::SpotifyAPI(std::string cliendID, std::string clientSecret) {				
	curl_global_init(CURL_GLOBAL_ALL);
	
	this->clientID = clientID;
	this->clientSecret = clientSecret;

	this->refreshToken = readFileAt("src/api/vars/refreshToken.txt");

	if (refreshToken != "") {
		requestAccessToken();
	} else {
		// requestAccessToken("authorization_code");
		requestRefreshToken();
		requestAccessToken();
	}
}

/**
 * Requests an access token from Spotify with an already obtained refresh token
 */
void SpotifyAPI::requestAccessToken() {
	std::string postData = "grant_type=refresh_token&refresh_token=" + refreshToken + "&client_id=" + clientID + "&client_secret=" + clientSecret;
	this->accessToken = curlUtils.POST("/api/token", "https://accounts.spotify.com", postData)["access_token"];
}

/**
 *  Requests a refresh token from Spotify with an already obtained acess token
 */
void SpotifyAPI::requestRefreshToken() {
	options_t options;
	options["client_id"] = clientID;
	options["response_type"] = "code";
	options["redirect_uri"] = "https://bphun.github.io";
	options["scope"] = "user-read-private%20user-read-email%20playlist-read-private%20playlist-read-collaborative%20qplaylist-modify-public%20playlist-modify-private%20user-follow-modify%20user-follow-read%20user-library-read%20user-library-modify%20user-read-private%20user-read-birthdate%20user-read-email%20user-top-read%20ugc-image-upload%20user-read-playback-state%20user-modify-playback-state%20user-read-currently-playing%20user-read-recently-played";
		
	std::cout << curlUtils.GET("/authorize/", "https://accounts.spotify.com", options) << std::endl;

	// this->refreshToken = curlUtils.GET("/authorize/", "https://accounts.spotify.com", options)["refresh_token"];
	// writeStringToFile(this->refreshToken, "vars/refreshToken.txt");
}

/**
 * Reads a file from the file at the designated path
 * 
 * @param filePath Path to the file that will be read
 * 
 * @return Contents of the designated file
 * 
 */
std::string SpotifyAPI::readFileAt(std::string filePath) {
	std::ifstream file;
	std::string str;

	file.open(filePath);
	if (!file) {
		fprintf(stderr, "Error opening file at %s\n", filePath.c_str());
		exit(-1);
	}

	file >> str;

	file.close();

	return str;
}

/**
 * Writes a string to the file at the designated path
 * 
 * @param str String that will be written to the file
 * @param filePath Path of the file that will be written to
 * 
 */
void SpotifyAPI::writeStringToFile(std::string str, std::string filePath) {
	std::ofstream file;
	file.open(filePath);

	if (!file) {
		printf("Error opening file %s\n", filePath.c_str());
		exit(-1);
	}

	file << str;
	file.close();
}

/**
 * Inserts a list of options into destination[key]
 * 
 * @param source Vector of strings that are inserted into an options_t map
 * @param key Map key where options will be inserted
 * @param destination A type alias of std::map<std::string, std::string> that stores options that will be aprsed by CurlUtils
 * 
 */
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


///	Album 

/**
 * Adds albums to the user's saved albums list
 * 
 * @param albumIds Albums that will be saved
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::saveAlbums(std::vector<std::string> albumIds, options_t options) {
	insertOptions(albumIds, "ids", options);
	curlUtils.PUT("/v1/me/albums", options, accessToken);
}

/**
 * Removes albums from a user's saved albums list
 * 
 * @param albumIds Albums that will be unsaved
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::removeSavedAlbums(std::vector<std::string> albumIds, options_t options) {
	insertOptions(albumIds, "ids", options);
	curlUtils.DELETE("/v1/me/albums", options, accessToken);
}

/**
 * Checks if an album has been saved to the user's saved albums list
 * 
 * @param albumIds Albums that will be cross-checked with user's saved albums list to determine if they have been saved
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return boolean representing all of the albums' save status
 * 
 */
bool SpotifyAPI::checkSavedAlbums(std::vector<std::string> albumIds, options_t options) {
	insertOptions(albumIds, "ids", options);
	return curlUtils.GET("/v1/me/albums/contains", options, accessToken)[0];
}

/**
 * Fetches an album from Spotify
 * 
 * @param albumID The album that will be fetched
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return The requested album
 * 
 */
Album SpotifyAPI::fetchAlbum(std::string albumID, options_t options) {
	return Album(curlUtils.GET("/v1/albums/" + albumID, options, accessToken));
}

/**
 * Fetches the latest releases on Spotify
 *
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of latest albums on Spotify
 * 
 */
Pager<Album> SpotifyAPI::fetchNewReleases(options_t options) {
	return Pager<Album>(curlUtils.GET("/v1/browse/new-releases", options, accessToken)["albums"]);
}

/**
 * Fetches all of the user's saved albums
 * 
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of the user's saved albums
 */
Pager<SavedAlbum> SpotifyAPI::fetchSavedAlbums(options_t options) {
	return Pager<SavedAlbum>(curlUtils.GET("/v1/me/albums", options, accessToken));
}

/**
 * Fetches all the tracks in an album
 *
 * @param albumID Album from which the tracks will be fetched
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of the album's tracks
 * 
 */
Pager<Track> SpotifyAPI::fetchAlbumTracks(std::string albumID, options_t options) {
	return Pager<Track>(curlUtils.GET("/v1/albums/" + albumID + "/tracks", options, accessToken));
}

/**
 * Runs a query through Spotify's search engine
 *
 * @param query Search query that will be sent to Spotify's search engine
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of albums returned from the spotify search engine
 * 
 */
Pager<Album> SpotifyAPI::searchAlbums(std::string query, options_t options) {
	options["type"] = "album";
	replaceAll(query, " ", "%20");
	options["q"] = query;
	return Pager<Album>(curlUtils.GET("/v1/search", options, accessToken)["albums"]);
}

/**
 * Fetches all of an artist's albums
 *
 * @param artistID Artist from which the albums will be fetched
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of the artist's albums
 * 
 */
Pager<Album> SpotifyAPI::fetchArtistAlbums(std::string artistID, options_t options) {
	return Pager<Album>(curlUtils.GET("/v1/artists/" + artistID + "/albums", options, accessToken));
}

/**
 * Fetches albums from Spotify
 *
 * @param albumIDs Albums that will be fetched from spotify
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Vector of the requested albums
 * 
 */
std::vector<Album> SpotifyAPI::fetchAlbums(std::vector<std::string> albumIDs, options_t options) {
	std::vector<Album> albums;
	for (std::string albumID : albumIDs) {
		albums.push_back(fetchAlbum(albumID, options));
	}
	return albums;
}


//	Artist

/**
 * Add's the artist to the user's followed artists list
 * 
 * @param artistID The artist that will be followed by the user
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::followArtist(std::string artistID, options_t options) {
	options["type"] = "artist";
	options["ids"] = artistID;
	curlUtils.PUT("/v1/me/following", options, accessToken);
}

/**
 * Checks if the user is following a specific artist
 * 
 * @param artistID The artist that will be cross-referenced with the user's following artist list
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return boolean that denotes if the user is following the artist
 * 
 */
bool SpotifyAPI::checkFollowingArtist(std::string artistID, options_t options) {
	options["type"] = "artist";
	options["ids"] = artistID;
	return curlUtils.GET("/v1/me/following/contains", options, accessToken)[0];
}

/**
 * Fetches a Spotify artist
 * 
 * @param artistID The artist that will be fetched
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return The requested artist
 * 
 */
Artist SpotifyAPI::fetchArtist(std::string artistID, options_t options) {
	return Artist(curlUtils.GET("/v1/artists/" + artistID, options, accessToken));
}

/**
 * Fetches the user's top artists (Based on how much a user listens to the artist)
 *
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return A pager of the user's top artists
 * 
 */
Pager<Artist> SpotifyAPI::fetchUserTopArtists(options_t options) {
	return Pager<Artist>(curlUtils.GET("/v1/me/top/artists", options, accessToken));
}

/**
 * Runs a query through Spotify's search engine
 *
 * @param query Search query that will be sent to Spotify's search engine
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of artists returned from the spotify search engine
 * 
 */
Pager<Artist> SpotifyAPI::searchArtists(std::string query, options_t options) {
	options["type"] = "artist";
	options["q"] = query;
	return Pager<Artist>(curlUtils.GET("/v1/search", options, accessToken)["artists"]);
}

/**
 * Fetches artists that are related to the specified artist
 *
 * @param artistID Artist that will be used to generate related artists
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return vector of related artists
 * 
 */
std::vector<Artist> SpotifyAPI::fetchArtistRelatedArtists(std::string artistID, options_t options) {
	std::vector<Artist> artists;
	nlohmann::json json = curlUtils.GET("/v1/artists/" + artistID + "/related-artists", options, accessToken);
	for(nlohmann::json artistJson : json["artists"]) {
		artists.push_back(Artist(artistJson));
	}
	return artists;
}

/**
 * Fetches specified artists
 *
 * @param artistIDs Artists that will be fetched
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return vector of requested artists
 * 
 */
std::vector<Artist> SpotifyAPI::fetchArtists(std::vector<std::string> artistIDs, options_t options) {
	std::vector<Artist> artists;
	for (std::string artistID : artistIDs) {
		artists.push_back(fetchArtist(artistID));
	}
	return artists;
}

/**
 * Fetches an artist's top tracks
 *
 * @param artistID Artist from which the top tracks will be collected
 * @param country Abbreviated country code (i.e United States = "US") used to prevent collecting tracks unavailable in the user's country
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return vector of the artist's top tracks
 * 
 */
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

/**
 * Edits a user's playists
 * 
 * @param userID User who owns the playlist that will be edited
 * @param playlistID Playlist that will be edited
 * @param options Edits that will be made to the the playlist
 * 
 */
void SpotifyAPI::editPlaylist(std::string userID, std::string playlistId, options_t options) {
	nlohmann::json bodyJson;
	for (auto option : options) {
		bodyJson[option.first] = option.second;
	}

	curlUtils.PUT("/v1/users/" + userID + "/playlists/" + playlistId, options_t(), accessToken, bodyJson.dump(4));
}

/**
 * Adds a playlist to the user's following playlist list
 * 
 * @param ownerID The owner of the playlist that will be followed by the user
 * @param playlistID Playlist that will be followed by the artist
 * @param options Options that will be sent to Spotify in the request header
 *
 */
void SpotifyAPI::followPlaylist(std::string ownerID, std::string playlistdID, options_t options) {
	curlUtils.PUT("/v1/users/" + ownerID + "/playlists/" + playlistdID + "/followers", options, accessToken);
}

/**
 * Removes a playlist from a user's followed playlist list
 * 
 * @param ownerID Owner of the playlist that will be unfollowed
 * @param playlistID Playlist that will be unfollowed
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::unfollowPlaylist(std::string ownerID, std::string playlistdID, options_t options) {
	curlUtils.DELETE("/v1/users/" + ownerID + "/playlists/" + playlistdID + "/followers", options, accessToken);
}

/**
 * Removes the specified tracks from a playlist
 * 
 * @param userID The owner of the playlist that will be modified
 * @param playlistID Playlist from which tracks will be removed
 * @param trackIDs Tracks that will be removed from the playlist
 * @param snapshotID The modified playlist's snapshotID
 * 
 */
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

/**
 * Adds tracks to a playlist
 * 
 * @param userID Owner of the playlist that will be modified
 * @param playlistID Playlist to which tracks will be added
 * @param trackUris The tracks that will be added to the playlist
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::addTracksToPlaylist(std::string userID, std::string playlistID, std::vector<std::string> trackUris, options_t options) {
	insertOptions(trackUris, "uris", options);
	curlUtils.POST("/v1/users/" + userID + "/playlists/" + playlistID + "/tracks", options, accessToken);
}

/**
 * Reorders a playlist in the specified range according to the specified order
 * 
 * @param userID Owner of the playlist that will be modified
 * @param playlistID Playlist that will be modified
 * @param rangeStart Starting index of the reorder
 * @param insertBefore Ending index of the reorder
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::reorderPlaylistTracks(std::string userID, std::string playlistID, int rangeStart, int insertBefore, options_t options) {
	nlohmann::json bodyJson;
	bodyJson["range_start"] = rangeStart;
	bodyJson["insert_before"] = insertBefore;
	for (auto option : options) {
		bodyJson[option.first] = option.second;
	}

	curlUtils.PUT("/v1/users/" + userID + "/playlists/" + playlistID + "/tracks", options_t(), accessToken, bodyJson.dump(4));
}

/**
 * Replaces tracks in a playlist with new tracks
 * 
 * @param userID Owner of the playlist that will be modified
 * @param playlistID Playlist that will be modified
 * @param trackUris Tracks that will be replacing the old tracks in a playlist
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::replacePlaylistTracks(std::string userID, std::string playlistID, std::vector<std::string> trackUris, options_t options) {
	insertOptions(trackUris, "uris", options);
	curlUtils.PUT("/v1/users/" + userID + "/playlists/" + playlistID + "/tracks", options, accessToken);
}

/**
 * Checks if multiple users are following a playlist
 * 
 * @param userID Owner of the playlist that will be cross-referenced
 * @param playlistID Playlist that will be cross-referenced against the users' followed playlist list
 * @param userIDs Users that will be checked if they are following a playlist
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return boolean denoting if all the users are following a playlist
 * 
 */
bool SpotifyAPI::checkUserFollowingPlaylist(std::string userID, std::string playlistID, std::vector<std::string> userIDs, options_t options) {
	insertOptions(userIDs, "ids", options);
	return curlUtils.GET("/v1/users/" + userID + "/playlists/" + playlistID + "/followers/contains", options, accessToken)[0];
}

/**
 * Creates a new playlist with specified name
 * 
 * @param userID User who will own the new playlist
 * @param name Name of the playlist that will be created
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return The newly created playlist
 * 
 */
Playlist SpotifyAPI::createPlaylist(std::string userID, std::string name, options_t options) {
	nlohmann::json bodyJson;
	bodyJson["name"] = name;
	for (auto option : options) {
		bodyJson[option.first] = option.second;
	}
	return Playlist(curlUtils.POST("/v1/users/" + userID + "/playlists", options_t(), accessToken, bodyJson.dump(4)));
}

/**
 * Fetches specified playlist
 * 
 * @param userID Owner of the playlist that will be fetched
 * @param playlistID The playlist that will be fetched
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return The playlist that was fetched
 * 
 */
Playlist SpotifyAPI::fetchPlaylist(std::string userID, std::string playlistID, options_t options) {
	return Playlist(curlUtils.GET("/v1/users/" + userID + "/playlists/" + playlistID, options, accessToken));
}

/**
 * Fetches all tracks in a playlist
 *
 * @param userID Owner of the playlist that will be fetched
 * @param playlistID Playlist that will be fetched
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of the playlist's tracks represented as a 'PlaylistTrack'
 */
Pager<PlaylistTrack> SpotifyAPI::fetchPlaylistTracks(std::string userID, std::string playlistID, options_t options) {
	return Pager<PlaylistTrack>(curlUtils.GET("/v1/users/" + userID + "/playlists/" + playlistID + "/tracks", options, accessToken));
}

/**
 * Fetches the current authorized user's playlists
 *
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of the user's playlists
 * 
 */
Pager<Playlist> SpotifyAPI::fetchUserPlaylists(options_t options) {
	return Pager<Playlist>(curlUtils.GET("/v1/me/playlists", options, accessToken));
}

/**
 * Fetches the currently featured playlists on Spotify
 *
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
Pager<Playlist> SpotifyAPI::fetchFeaturedPlaylists(options_t options) {
	return Pager<Playlist>(curlUtils.GET("/v1/browse/featured-playlists", options, accessToken)["playlists"]);
}

/**
 * Runs a query through Spotify's search engine
 *
 * @param query Search query that will be sent to Spotify's search engine
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of playlist returned from the spotify search engine
 * 
 */
Pager<Playlist> SpotifyAPI::searchPlaylists(std::string query, options_t options) {
	options["type"] = "playlist";
	options["q"] = query;
	return Pager<Playlist>(curlUtils.GET("/v1/search", options, accessToken)["playlists"]);
}

/**
 * Fetches playlists owned by a specified user
 *
 * @param userID User from which the playlists will be fetched
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of the user's playlists
 * 
 */
Pager<Playlist> SpotifyAPI::fetchUserPlaylists(std::string userID, options_t options) {
	return Pager<Playlist>(curlUtils.GET("/v1/users/" + userID + "/playlists", options, accessToken));
}


//	Tracks

/**
 * Adds tracks to the currently authorized user's saved tracks list
 * 
 * @param trackIDs The tracks that will be saved to the user's saved tracks list
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::saveTracks(std::vector<std::string> trackIDs, options_t options) {
	insertOptions(trackIDs, "ids", options);
	curlUtils.PUT("/v1/me/tracks", options, accessToken);
}

/**
 * Removes tracks from the currently authorized user's saved tracks list
 * 
 * @param trackIDs Tracks that will be removed from the currently authorized user's saved tracks list
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::unsaveTracks(std::vector<std::string> trackIDs, options_t options) {
	insertOptions(trackIDs, "ids", options);
	curlUtils.DELETE("/v1/me/tracks", options, accessToken);
}

/**
 * Checks if the currently authorized user is following a track
 * 
 * @param trackIDs The tracks that will be checked if the user is following them
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return boolean denoting the user's follow status of all the playlists
 * 
 */
bool SpotifyAPI::checkSavedTracks(std::vector<std::string> trackIDs, options_t options) {
	insertOptions(trackIDs, "ids", options);
	return curlUtils.GET("/v1/me/tracks/contains", options, accessToken)[0];
}

/**
 * Fetches a Spotify track
 * 
 * @param trackID The track that will be fetched
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return The fetched track
 * 
 */
Track SpotifyAPI::fetchTrack(std::string trackID, options_t options) {
	return Track(curlUtils.GET("/v1/tracks/" + trackID, options, accessToken));
}

/**
 * Fetches recommended tracks for the user
 * 
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return The user's recommended tracks
 */
Recommendations SpotifyAPI::fetchRecommendations(options_t options) {
	return Recommendations(curlUtils.GET("/v1/recommendations", options, accessToken));
}

// CurrentlyPlayingTrack SpotifyAPI::fetchUserCurrentPlayingTrack(options_t options) {

// }

/**
 * Fetches the user's saved tracks
 *
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of the user's saved tracks
 * 
 */
Pager<SavedTrack> SpotifyAPI::fetchSavedTracks(options_t options) {
	return Pager<SavedTrack>(curlUtils.GET("/v1/me/tracks", options, accessToken));
}

/**
 * Fetches the user's saved tracks
 *
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
Pager<Track> SpotifyAPI::fetchUserTopTracks(options_t options) {
	return Pager<Track>(curlUtils.GET("/v1/me/top/tracks", options, accessToken));
}

/**
 * Runs a query through Spotify's search engine
 *
 * @param query Search query that will be sent to Spotify's search engine
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of tracks returned from the spotify search engine
 * 
 */
Pager<Track> SpotifyAPI::searchTracks(std::string query, options_t options) {
	options["type"] = "track";
	options["q"] = query;
	return Pager<Track>(curlUtils.GET("/v1/search", options, accessToken)["tracks"]);
}

/**
 * Fetches the specified tracks
 *
 * @param trackIDs The tracks that will be fetched
 *
 * @return vector of the requested tracks
 * 
 */
std::vector<Track> SpotifyAPI::fetchTracks(std::vector<std::string> trackIDs, options_t options) {
	std::vector<Track> tracks;
	for(std::string trackID : trackIDs) {
		tracks.push_back(fetchTrack(trackID, options));
	}
	return tracks;
}


//	playback

/**
 * Fetches all of the tracks that the user has recently listend to
 *
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Cursor pager of the user's play history
 * 
 */
CursorPager<PlayHistory> SpotifyAPI::fetchUserRecentlyPlayed(options_t options) {
	return CursorPager<PlayHistory>(curlUtils.GET("/v1/me/player/recently-played", options, accessToken));
}

/**
 * Collects the user's current context
 * 
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return User's current playing context
 * 
 */
CurrentlyPlayingContext SpotifyAPI::fetchUserCurrentPlayback(options_t options) {
	return CurrentlyPlayingContext(curlUtils.GET("/v1/me/player", options, accessToken));
}

/**
 * Fetches devices that the user has authorized to access their Spotify account
 *
 * @return vector of the user's authenticated devices
 * 
 */
std::vector<Device> SpotifyAPI::fetchUserDevices(options_t options) {
	std::vector<Device> devices;
	nlohmann::json devicesJson = curlUtils.GET("/v1/me/player/devices", options, accessToken);
	for (nlohmann::json deviceJson : devicesJson["devices"]) {
		devices.push_back(Device(deviceJson));
	}
	return devices;
} 

//	User

/**
 * Follows a specified user
 * 
 * @param userID User that will be followed
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::followUser(std::string userID, options_t options) {
	options["type"] = "user";
	options["ids"] = userID;
	curlUtils.PUT("/v1/me/following", options, accessToken);
}

/**
 * Unfollows a specified user
 * 
 * @param userID User that will be unfollowed
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::unfollowUser(std::string userID, options_t options) {
	options["type"] = "user";
	options["ids"] = userID;
	curlUtils.DELETE("/v1/me/following", options, accessToken);
}

/**
 * Checks if the current user is following a user
 * 
 * @param userID the user that will be cross-referenced
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return boolean denoting whether or not the current user is following the specified user
 * 
 */
bool SpotifyAPI::checkFollowingUser(std::string userID, options_t options) {
	options["type"] = "user";
	options["ids"] = userID;
	return curlUtils.GET("/v1/me/following/contains", options, accessToken)[0];
}

/**
 * Fetches the currently authenticated user
 * 
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return The currently authenticated user
 * 
 */
User SpotifyAPI::fetchUser(options_t options) {
	return User(curlUtils.GET("/v1/me", options, accessToken));
}


//	Stream Control

/**
 * Pauses the user's current stream session
 * 
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::pause(options_t options) {
	curlUtils.PUT("/v1/me/player/pause", options, accessToken);
}

/**
 * Resumes playing of the current user's stream session
 * 
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::play(options_t options) {
	curlUtils.PUT("/v1/me/player/play", options, accessToken);
}

/**
 * Skips to the next song in the user's play queue
 * 
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::skipToNext(options_t options) {
	curlUtils.POST("/v1/me/player/next", options, accessToken);
}

/**
 * Skips to the previous song in the user's play queue
 * 
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::skipToPrevious(options_t options) {
	curlUtils.POST("/v1/me/player/previous", options, accessToken);
}

/**
 * Sets the shuffle state of the user's player
 * 
 * @param state boolean representing toggle state
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::toggleShuffle(bool state, options_t options) {
	options["state"] = state;
	curlUtils.PUT("/v1/me/player/shuffle", options, accessToken);
}

/**
 * Sets the repeat of the user's player to either track, context, or off
 * 
 * @param state State of the user's player's repeat mode ("track", "context", "off")
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::setRepeat(std::string state, options_t options) {
	options["state"] = state;
	curlUtils.PUT("/v1/me/player/repeat", options, accessToken);
}

/**
 * Sets the volume of the user's current stream session
 * 
 * @param volumePercent The volume level of the user's audio
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::setVolume(int volumePercent, options_t options) {
	options["volume_percent"] = volumePercent;
	curlUtils.PUT("/v1/me/player/volume", options, accessToken);
}

/**
 * Transfers the current stream session to a new device
 * 
 * @param deviceId the device where the stream will be transferred to
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyAPI::transferUserPlayback(std::string deviceId, options_t options) {
	options["device_ids"] = deviceId;
	curlUtils.PUT("/v1/me/player", options, accessToken);
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
std::string SpotifyAPI::replaceAll(std::string& str, const std::string from, const std::string to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}


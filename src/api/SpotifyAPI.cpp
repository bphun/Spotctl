#include "SpotifyApi.h"

/**
 * Initializes the Spotify API and prepares it for requests to the Web API.
 * Connects to remote server to fetch the client ID and secret.
 */
SpotifyApi::SpotifyApi() {				
	// curl_global_init(CURL_GLOBAL_ALL);

	this->spotifyClientSecret = readFileAt("src/api/vars/spotifyClientSecret.txt");
	this->spotifyClientID = readFileAt("src/api/vars/spotifyClientId.txt");
	this->refreshToken = readFileAt("src/api/vars/refreshToken.txt");

	if (refreshToken != "") {
		requestAccessToken();
		isUserAuthenticated = true;
	} else {
		isUserAuthenticated = false;
	}
} 

/**
 * Authenticates a user using the provided authorization code by executing a POST request to the /api/token endpoint of spotify's account service
 * @param authorizationCode string given to user by opening the accounts endpoint
 */
void SpotifyApi::authenticateSpotifyUser(std::string authorizationCode) {
	nlohmann::json data = curlUtils.POST("/api/token/", "https://accounts.spotify.com", "client_id=" + spotifyClientID + 
	                                     "&client_secret=" + spotifyClientSecret + "&code=" + authorizationCode + 
	                                     "&grant_type=authorization_code" + "&redirect_uri=" + "https://bphun.github.io/callback/index.html");
	
	this->accessToken = data["access_token"];
	this->refreshToken = data["refresh_token"];

	writeStringToFile(refreshToken, "src/api/vars/refreshToken.txt");
}

/**
 * Creates a new Spotify Client user with the specified username and password
 * 
 * @param username Username of the user that will be created
 * @param password Password of the user that will be created
 * 
 * @return boolean. True if the accounted was created successfully, false if account creation failed.
 */
bool SpotifyApi::createClientUser(std::string username, std::string password) {
	std::string body = "{\"username\":\"" + username + "\",\"password\":\"" + password + "\"}";

	curlUtils.addHeader("Content-Type", "application/json");
	nlohmann::json responseBody = curlUtils.POST("/signup", backendURL, body);

	return responseBody["error"] == "";
}

/**
 * Authenticate an existing Spotify Client user with the specified username and password
 * 
 * @param username Username of the user that is being authenticated
 * @param password Password of the user that is being authenticated
 * 
 * @return boolean. True if authentication was successfull, false if authentication failed.
 */
bool SpotifyApi::authenticateClientUser(std::string username, std::string password) {
	std::string body = "{\"username\":\"" + username + "\",\"password\":\"" + password + "\"}";

	curlUtils.addHeader("Content-Type", "application/json");
	nlohmann::json responseBody = curlUtils.POST("/authentication", backendURL, body);

	clientAuthenticationCode = responseBody["authentication"];

	return responseBody["error"] == "";
}

/**
 * Logouts the current user by clearing the user's refresh token
 */
void SpotifyApi::logout() {
	writeStringToFile("", "src/api/vars/refreshToken.txt");
	// writeStringToFile("", "src/api/vars/spotifyClientId.txt");
	// writeStringToFile("", "src/api/vars/refreshToken.txt");
}

/**
 * Used to determine if the user has been successfully authenticated through the spotify web API
 * @return true if user has been authenticated and false if the user has not been authenticated
 */
bool SpotifyApi::userAuthenticated() {
	return isUserAuthenticated;
}

/**
 * Requests an access token from Spotify with an already obtained refresh token
 */
void SpotifyApi::requestAccessToken() {
	std::string postData = "grant_type=refresh_token&refresh_token=" + refreshToken + 
	"&client_id=" + spotifyClientID + 
	"&client_secret=" + spotifyClientSecret;
	this->accessToken = curlUtils.POST("/api/token", "https://accounts.spotify.com", postData)["access_token"];
}

/**
 * Reads a file from the file at the designated path
 * 
 * @param filePath Path to the file that will be read
 * 
 * @return Contents of the designated file
 * 
 */
std::string SpotifyApi::readFileAt(std::string filePath) {
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
void SpotifyApi::writeStringToFile(std::string str, std::string filePath) {
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
void SpotifyApi::insertOptions(std::vector<std::string> source, std::string key, options_t &destination) {
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
void SpotifyApi::saveAlbums(std::vector<std::string> albumIds, options_t options) {
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
void SpotifyApi::removeSavedAlbums(std::vector<std::string> albumIds, options_t options) {
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
bool SpotifyApi::checkSavedAlbums(std::vector<std::string> albumIds, options_t options) {
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
Album SpotifyApi::fetchAlbum(std::string albumID, options_t options) {
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
Pager<Album> SpotifyApi::fetchNewReleases(options_t options) {
	return Pager<Album>(curlUtils.GET("/v1/browse/new-releases", options, accessToken)["albums"]);
}

/**
 * Fetches all of the user's saved albums
 * 
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of the user's saved albums
 */
Pager<SavedAlbum> SpotifyApi::fetchSavedAlbums(options_t options) {
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
Pager<Track> SpotifyApi::fetchAlbumTracks(std::string albumID, options_t options) {
	return Pager<Track>(curlUtils.GET("/v1/albums/" + albumID + "/tracks", options, accessToken));
}

/**
 * Searches Spotify for albums with the specified query
 *
 * @param query Search query that will be sent to Spotify's search engine
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of albums returned from the spotify search engine
 * 
 */
Pager<Album> SpotifyApi::searchAlbums(std::string query, options_t options) {
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
Pager<Album> SpotifyApi::fetchArtistAlbums(std::string artistID, options_t options) {
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
std::vector<Album> SpotifyApi::fetchAlbums(std::vector<std::string> albumIDs, options_t options) {
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
void SpotifyApi::followArtist(std::string artistID, options_t options) {
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
bool SpotifyApi::checkFollowingArtist(std::string artistID, options_t options) {
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
Artist SpotifyApi::fetchArtist(std::string artistID, options_t options) {
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
Pager<Artist> SpotifyApi::fetchUserTopArtists(options_t options) {
	return Pager<Artist>(curlUtils.GET("/v1/me/top/artists", options, accessToken));
}

/**
 * Searches Spotify for an artists that match a query
 *
 * @param query Search query that will be sent to Spotify's search engine
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of artists returned from the spotify search engine
 * 
 */
Pager<Artist> SpotifyApi::searchArtists(std::string query, options_t options) {
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
std::vector<Artist> SpotifyApi::fetchArtistRelatedArtists(std::string artistID, options_t options) {
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
std::vector<Artist> SpotifyApi::fetchArtists(std::vector<std::string> artistIDs, options_t options) {
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
std::vector<Track> SpotifyApi::fetchArtistTopTracks(std::string artistID, std::string country, options_t options) {
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
void SpotifyApi::editPlaylist(std::string userID, std::string playlistId, options_t options) {
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
void SpotifyApi::followPlaylist(std::string ownerID, std::string playlistdID, options_t options) {
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
void SpotifyApi::unfollowPlaylist(std::string ownerID, std::string playlistdID, options_t options) {
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
void SpotifyApi::removeTracksFromPlaylist(std::string userID, std::string playlistId, std::vector<std::string> trackIDs, std::string snapshotID) {
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
void SpotifyApi::addTracksToPlaylist(std::string userID, std::string playlistID, std::vector<std::string> trackUris, options_t options) {
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
void SpotifyApi::reorderPlaylistTracks(std::string userID, std::string playlistID, int rangeStart, int insertBefore, options_t options) {
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
void SpotifyApi::replacePlaylistTracks(std::string userID, std::string playlistID, std::vector<std::string> trackUris, options_t options) {
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
bool SpotifyApi::checkUserFollowingPlaylist(std::string userID, std::string playlistID, std::vector<std::string> userIDs, options_t options) {
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
Playlist SpotifyApi::createPlaylist(std::string userID, std::string name, options_t options) {
	nlohmann::json bodyJson;
	bodyJson["name"] = name;
	for (auto option : options) {
		bodyJson[option.first] = option.second;
	}
	std::cout << bodyJson.dump() << std::endl;
	return Playlist(curlUtils.POST("/v1/users/" + userID + "/playlists", options_t(), accessToken, bodyJson.dump()));
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
Playlist SpotifyApi::fetchPlaylist(std::string userID, std::string playlistID, options_t options) {
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
Pager<PlaylistTrack> SpotifyApi::fetchPlaylistTracks(std::string userID, std::string playlistID, options_t options) {
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
Pager<Playlist> SpotifyApi::fetchUserPlaylists(options_t options) {
	return Pager<Playlist>(curlUtils.GET("/v1/me/playlists", options, accessToken));
}

/**
 * Fetches the currently featured playlists on Spotify
 *
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
Pager<Playlist> SpotifyApi::fetchFeaturedPlaylists(options_t options) {
	return Pager<Playlist>(curlUtils.GET("/v1/browse/featured-playlists", options, accessToken)["playlists"]);
}

/**
 * Searches Spotify for playlists that match a query
 *
 * @param query Search query that will be sent to Spotify's search engine
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of playlist returned from the spotify search engine
 * 
 */
Pager<Playlist> SpotifyApi::searchPlaylists(std::string query, options_t options) {
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
Pager<Playlist> SpotifyApi::fetchUserPlaylists(std::string userID, options_t options) {
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
void SpotifyApi::saveTracks(std::vector<std::string> trackIDs, options_t options) {
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
void SpotifyApi::unsaveTracks(std::vector<std::string> trackIDs, options_t options) {
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
bool SpotifyApi::checkSavedTracks(std::vector<std::string> trackIDs, options_t options) {
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
Track SpotifyApi::fetchTrack(std::string trackID, options_t options) {
	return Track(curlUtils.GET("/v1/tracks/" + trackID, options, accessToken));
}

/**
 * Fetches recommended tracks for the user
 * 
 * @param options Options that will be sent to Spotify in the request header
 * 
 * @return The user's recommended tracks
 */
Recommendations SpotifyApi::fetchRecommendations(options_t options) {
	return Recommendations(curlUtils.GET("/v1/recommendations", options, accessToken));
}

// CurrentlyPlayingTrack SpotifyApi::fetchUserCurrentPlayingTrack(options_t options) {

// }

/**
 * Fetches the user's saved tracks
 *
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of the user's saved tracks
 * 
 */
Pager<SavedTrack> SpotifyApi::fetchSavedTracks(options_t options) {
	return Pager<SavedTrack>(curlUtils.GET("/v1/me/tracks", options, accessToken));
}

/**
 * Fetches the user's saved tracks
 *
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
Pager<Track> SpotifyApi::fetchUserTopTracks(options_t options) {
	return Pager<Track>(curlUtils.GET("/v1/me/top/tracks", options, accessToken));
}

/**
 * Searches Spotify for tracks that match a query
 *
 * @param query Search query that will be sent to Spotify's search engine
 * @param options Options that will be sent to Spotify in the request header
 *
 * @return Pager of tracks returned from the spotify search engine
 * 
 */
Pager<Track> SpotifyApi::searchTracks(std::string query, options_t options) {
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
std::vector<Track> SpotifyApi::fetchTracks(std::vector<std::string> trackIDs, options_t options) {
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
CursorPager<PlayHistory> SpotifyApi::fetchUserRecentlyPlayed(options_t options) {
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
CurrentlyPlayingContext SpotifyApi::fetchUserCurrentPlayback(options_t options) {
	return CurrentlyPlayingContext(curlUtils.GET("/v1/me/player", options, accessToken));
}

/**
 * Fetches devices that the user has authorized to access their Spotify account
 *
 * @return vector of the user's authenticated devices
 * 
 */
std::vector<Device> SpotifyApi::fetchUserDevices(options_t options) {
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
void SpotifyApi::followUser(std::string userID, options_t options) {
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
void SpotifyApi::unfollowUser(std::string userID, options_t options) {
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
bool SpotifyApi::checkFollowingUser(std::string userID, options_t options) {
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
User SpotifyApi::fetchUser(options_t options) {
	return User(curlUtils.GET("/v1/me", options, accessToken));
}


//	Stream Control

/**
 * Pauses the user's current stream session
 * 
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyApi::pause(options_t options) {
	curlUtils.PUT("/v1/me/player/pause", options, accessToken);
}

/**
 * Resumes playing of the current user's stream session
 * 
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyApi::play(options_t options) {
	curlUtils.PUT("/v1/me/player/play", options, accessToken, options["context_uri"]);
}

/**
 * Skips to the next song in the user's play queue
 * 
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyApi::skipToNext(options_t options) {
	curlUtils.POST("/v1/me/player/next", options, accessToken);
}

/**
 * Skips to the previous song in the user's play queue
 * 
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyApi::skipToPrevious(options_t options) {
	curlUtils.POST("/v1/me/player/previous", options, accessToken);
}

/**
 * Sets the shuffle state of the user's player
 * 
 * @param state boolean representing toggle state
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyApi::toggleShuffle(bool state, options_t options) {
	options["state"] = (state == true ? "true" : "false");
	curlUtils.PUT("/v1/me/player/shuffle", options, accessToken);
}

/**
 * Sets the repeat of the user's player to either track, context, or off
 * 
 * @param state State of the user's player's repeat mode ("track", "context", "off")
 * @param options Options that will be sent to Spotify in the request header
 * 
 */
void SpotifyApi::setRepeat(std::string state, options_t options) {
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
void SpotifyApi::setVolume(int volumePercent, options_t options) {
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
void SpotifyApi::transferUserPlayback(std::string deviceId, options_t options) {
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
std::string SpotifyApi::replaceAll(std::string& str, const std::string from, const std::string to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}


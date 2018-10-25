#ifndef SPOTIFY_API_H
#define SPOTIFY_API_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>

#include <curl/curl.h>

#include "models/Pager.h"
#include "models/Track.h"
#include "models/Album.h"
#include "models/Artist.h"
#include "models/Device.h"
#include "models/Playlist.h"
#include "models/UserPublic.h"
#include "models/SavedAlbum.h"
#include "models/SavedTrack.h"
#include "models/CursorPager.h"
#include "models/PlayHistory.h"
#include "models/PlaylistTrack.h"
#include "models/Recommendations.h"
#include "models/CurrentlyPlayingTrack.h"
#include "models/CurrentlyPlayingContext.h"

#include "utils/json/json.hpp"
#include "utils/CurlUtils.h"
#include "utils/CurlException.h"
#include "utils/SpotifyException.h"

typedef std::map<std::string, std::string> options_t;

class SpotifyAPI {

private:

	std::string clientID;
	std::string accessToken;
	std::string refreshToken;
	std::string clientSecret;
	std::string authorizationCode;
	CurlUtils curlUtils;

	void requestAccessToken(std::string grantType);
	void insertOptions(std::vector<std::string> source, std::string key, options_t &destination);
	std::string replaceAll(std::string& str, const std::string from, const std::string to);
	std::string readFileAt(std::string path);

public:

	SpotifyAPI();


	//	Album 

	void saveAlbums(std::vector<std::string> albumIds, options_t options = options_t());
	void removeSavedAlbums(std::vector<std::string> albumIds, options_t options = options_t());
	bool checkSavedAlbums(std::vector<std::string> albumIds, options_t options = options_t());
	Album fetchAlbum(std::string albumID, options_t options = options_t());
	Pager<Album> fetchNewReleases(options_t options = options_t());
	Pager<SavedAlbum> fetchSavedAlbums(options_t options = options_t());
	Pager<Track> fetchAlbumTracks(std::string albumID, options_t = options_t());
	Pager<Album> searchAlbums(std::string query, options_t options = options_t());
	Pager<Album> fetchArtistAlbums(std::string artistID, options_t options = options_t());
	std::vector<Album> fetchAlbums(std::vector<std::string> albumIDs, options_t options = options_t());


	//	Artist

	void followArtist(std::string artistID, options_t options = options_t());
	bool checkFollowingArtist(std::string artistID, options_t options = options_t());
	Artist fetchArtist(std::string artistID, options_t options = options_t());
	Pager<Artist> fetchUserTopArtists(options_t options = options_t());
	Pager<Artist> searchArtists(std::string query, options_t options = options_t());
	std::vector<Artist> fetchArtistRelatedArtists(std::string artistID, options_t options = options_t());
	std::vector<Artist> fetchArtists(std::vector<std::string> artistIDs, options_t options = options_t());
	std::vector<Track> fetchArtistTopTracks(std::string artistID, std::string country, options_t options = options_t());


	//	Playlist

	void editPlaylist(std::string userId, std::string playlistId, options_t options = options_t());
	void followPlaylist(std::string ownerID, std::string playlistdID, options_t options = options_t());
	void unfollowPlaylist(std::string ownerID, std::string playlistdID, options_t options = options_t());
	void removeTracksFromPlaylist(std::string userID, std::string playlistId, std::vector<std::string> trackIDs, std::string snapshotID);
	void addTracksToPlaylist(std::string userId, std::string playlistId, std::vector<std::string> trackUris, options_t options = options_t());
	void reorderPlaylistTracks(std::string userId, std::string playlistId, int rangeStart, int insertBefore, options_t options = options_t());
	void replacePlaylistTracks(std::string userId, std::string playlistId, std::vector<std::string> trackUris, options_t options = options_t());
	bool checkUserFollowingPlaylist(std::string userId, std::string playlistId, std::vector<std::string> userIds, options_t options = options_t());
	Playlist createPlaylist(std::string userID, std::string name, options_t options = options_t());
	Playlist fetchPlaylist(std::string userId, std::string playlistId, options_t options = options_t());
	Pager<PlaylistTrack> fetchPlaylistTracks(std::string userId, std::string playlistId, options_t options = options_t());
	Pager<Playlist> fetchUserPlaylists(options_t options = options_t());
	Pager<Playlist> fetchFeaturedPlaylists(options_t options = options_t());
	Pager<Playlist> searchPlaylists(std::string query, options_t options = options_t());
	Pager<Playlist> fetchUserPlaylists(std::string userId, options_t options = options_t());


	//	Tracks

	void saveTracks(std::vector<std::string> trackIDs, options_t options = options_t());
	void unsaveTracks(std::vector<std::string> trackIDs, options_t options = options_t());
	bool checkSavedTracks(std::vector<std::string> trackIDs, options_t options = options_t());
	Track fetchTrack(std::string trackID, options_t options = options_t());
	Recommendations fetchRecommendations(options_t options = options_t());
	CurrentlyPlayingTrack fetchUserCurrentPlayingTrack(options_t options = options_t());
	Pager<SavedTrack> fetchSavedTracks(options_t options = options_t());
	Pager<Track> fetchUserTopTracks(options_t options = options_t());
	Pager<Track> searchTracks(std::string query, options_t options = options_t());
	std::vector<Track> fetchTracks(std::vector<std::string> trackIds, options_t options = options_t());


	//	playback

	CursorPager<PlayHistory> fetchUserRecentlyPlayed(options_t options = options_t());
	CurrentlyPlayingContext fetchUserCurrentPlayback(options_t options = options_t());
	std::vector<Device> fetchUserDevices(options_t options = options_t());


	//	User

	void followUser(std::string userID, options_t options = options_t());
	void unfollowUser(std::string userID, options_t options = options_t());
	bool checkFollowingUser(std::string userID, options_t options = options_t());
	User fetchUser(options_t options = options_t());


	//	Stream Control

	void pause(options_t options = options_t());
	void play(options_t options = options_t());
	void skipToNext(options_t options = options_t());
	void skipToPrevious(options_t options = options_t());
	void toggleShuffle(bool state, options_t options = options_t());
	void setRepeat(std::string state, options_t options = options_t());
	void setVolume(int volumePercent, options_t options = options_t());
	void transferUserPlayback(std::string deviceId, options_t options = options_t());

};

#endif

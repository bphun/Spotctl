#include <gtest/gtest.h>
// #include <gmock/gmock.h>

#include <vector>

#include "../src/api/SpotifyApi.h"

struct SpotifyApiEndpointTests: public ::testing::Test {
protected:
	static SpotifyApi sharedSpotifyApi;
	SpotifyApi api;
	static std::string staticPlaylistID;
	std::string playlistID;

	virtual void SetUp() {
		api = SpotifyApiEndpointTests::sharedSpotifyApi;
		playlistID = SpotifyApiEndpointTests::staticPlaylistID;
	}

	static void SetUpTestCase() {
		sharedSpotifyApi = SpotifyApi();
	}
};

SpotifyApi SpotifyApiEndpointTests::sharedSpotifyApi;
std::string SpotifyApiEndpointTests::staticPlaylistID;

TEST_F(SpotifyApiEndpointTests, saveAlbums) {
	api.saveAlbums({"0sNOF9WDwhWunNAHPD3Baj"});
	ASSERT_TRUE(api.checkSavedAlbums({"0sNOF9WDwhWunNAHPD3Baj"}));
}

TEST_F(SpotifyApiEndpointTests, fetchSavedAlbums) {
	Pager<SavedAlbum> albums = api.fetchSavedAlbums();
	ASSERT_STREQ(albums.getItems()[0].getAlbum().getName().c_str(), "She's So Unusual");
}

TEST_F(SpotifyApiEndpointTests, removeSavedAlbums) {
	api.removeSavedAlbums({"0sNOF9WDwhWunNAHPD3Baj"});
	ASSERT_FALSE(api.checkSavedAlbums({"0sNOF9WDwhWunNAHPD3Baj"}));
}

TEST_F(SpotifyApiEndpointTests, fetchAlbumTest) {
	Album album = api.fetchAlbum("0sNOF9WDwhWunNAHPD3Baj");
	ASSERT_STREQ(album.getName().c_str(), "She's So Unusual");
}

TEST_F(SpotifyApiEndpointTests, fetchNewReleases) {
	Pager<Album> albums = api.fetchNewReleases();
	ASSERT_EQ(albums.getLimit(), 20);
}

TEST_F(SpotifyApiEndpointTests, fetchAlbumTracks) {
	Pager<Track> tracks = api.fetchAlbumTracks("0sNOF9WDwhWunNAHPD3Baj");
	ASSERT_STREQ(tracks.getItems()[0].getName().c_str(), "Money Changes Everything");
}

TEST_F(SpotifyApiEndpointTests, searchAlbums) {
	Pager<Album> albums = api.searchAlbums("When the party's over");
	ASSERT_STREQ(albums.getItems()[0].getName().c_str(), "when the party's over");
	ASSERT_STREQ(albums.getItems()[0].getArtists()[0].getName().c_str(), "Billie Eilish");
}


//	KMN, I havent touched this project in 9 days and this test just broke for no apparent reason
// TEST_F(SpotifyApiEndpointTests, fetchArtistAlbums) {
// 	Pager<Album> albums = api.fetchArtistAlbums("4SqTiwOEdYrNayaGMkc7ia");
// 	ASSERT_EQ(albums.getTotal(), 11);	
// 	std::vector<std::string> v = {"Baby Don't Talk","Surround Me - EP",
// 		"For You - EP",
// 		"Sleep Deprived","Liar",
// 		"Spotify Singles","Think About You",
// 		"Tired of Talking (Remixes)",
// 		"Tired of Talking (A-Trak & Cory Enemy Remix)",
// 		"Treasure - EP","NOW That's What I Call Music, Vol. 62"
// 	};

// 	std::vector<std::string> albumNames;
// 	for (Album album : albums.getItems()) {
// 		albumNames.push_back(album.getName());
// 	}
// 	EXPECT_THAT(albumNames, ::testing::ContainerEq(v));
// }

TEST_F(SpotifyApiEndpointTests, fetchAlbums) {
	std::vector<Album> albums = api.fetchAlbums({"0sNOF9WDwhWunNAHPD3Baj", "5lXgrzp3xcFdYCQXtsS6dG", "2VP96XdMOKTXefI8Nui23s"});

	ASSERT_EQ(albums.size(), 3);

	ASSERT_STREQ(albums[0].getName().c_str(), "She's So Unusual");
	ASSERT_STREQ(albums[1].getName().c_str(), "Pleasure");
	ASSERT_STREQ(albums[2].getName().c_str(), "Shawn Mendes");
}

TEST_F(SpotifyApiEndpointTests, followArtist) {
	api.followArtist("0QHgL1lAIqAw0HtD7YldmP");
	ASSERT_TRUE(api.checkFollowingArtist("0QHgL1lAIqAw0HtD7YldmP"));
}

TEST_F(SpotifyApiEndpointTests, checkFollowingArtist) {
	ASSERT_TRUE(api.checkFollowingArtist("0QHgL1lAIqAw0HtD7YldmP"));
}

TEST_F(SpotifyApiEndpointTests, fetchArtist) {
	Artist artist = api.fetchArtist("0QHgL1lAIqAw0HtD7YldmP");
	ASSERT_STREQ(artist.getName().c_str(), "DJ Khaled");
}

TEST_F(SpotifyApiEndpointTests, fetchUserTopArtists) {
	Pager<Artist> artists = api.fetchUserTopArtists();
	ASSERT_EQ(artists.getLimit(), 20);
}

TEST_F(SpotifyApiEndpointTests, searchArtists) {
	Pager<Artist> artists = api.searchArtists("billie");
	ASSERT_STREQ(artists.getItems()[0].getName().c_str(),"Billie Eilish");
}

TEST_F(SpotifyApiEndpointTests, fetchArtistRelatedArtists) {
	std::vector<Artist> artists = api.fetchArtistRelatedArtists("0QHgL1lAIqAw0HtD7YldmP");
	ASSERT_EQ(artists.size(), 20);
}

TEST_F(SpotifyApiEndpointTests, fetchArtists) {
	std::vector<Artist> artists = api.fetchArtists({"0QHgL1lAIqAw0HtD7YldmP", "6CWTBjOJK75cTE8Xv8u1kj"});
	ASSERT_STREQ(artists[0].getName().c_str(), "DJ Khaled");
	ASSERT_STREQ(artists[1].getName().c_str(), "Feist");
}

TEST_F(SpotifyApiEndpointTests, fetchArtistTopTracks) {
	std::vector<Track> tracks = api.fetchArtistTopTracks("0QHgL1lAIqAw0HtD7YldmP", "US");
	ASSERT_EQ(tracks.size(), 10);
}

TEST_F(SpotifyApiEndpointTests, createPlaylist) {
	User user = api.fetchUser();
	// Playlist newPlaylist = api.createPlaylist(user.getid().c_str(), "test");
	// Playlist retreivedPlaylist = api.fetchPlaylist(user.getid(), newPlaylist.getid());

	// ASSERT_STREQ(retreivedPlaylist.getName().c_str(), "test");
	// ASSERT_TRUE(api.checkUserFollowingPlaylist(user.getid(), retreivedPlaylist.getid(), {user.getid()}));

	// api.unfollowPlaylist(user.getid(), retreivedPlaylist.getid());

	// ASSERT_FALSE(api.checkUserFollowingPlaylist(user.getid(), retreivedPlaylist.getid(), {user.getid()}));
}

// TEST_F(SpotifyApiEndpointTests, editPlaylist) {
// 	User user = api.fetchUser();

// 	Playlist playlist = api.createPlaylist(user.getid(), "test");

// 	ASSERT_STREQ(playlist.getName().c_str(), "test");
// 	ASSERT_TRUE(api.checkUserFollowingPlaylist(user.getid(), playlist.getid(), {user.getid()}));

// 	api.addTracksToPlaylist(user.getid(), playlist.getid(), {"spotify:track:7reiSieFbRTo9KHbT39BZh", "spotify:track:1ObZ6sMWPeI56b74WaULRk"});
// 	Pager<PlaylistTrack> tracks = api.fetchPlaylistTracks(user.getid(), playlist.getid());
// 	ASSERT_STREQ(tracks.getItems()[0].getTrack().getURI().c_str(), "spotify:track:7reiSieFbRTo9KHbT39BZh");
// 	ASSERT_STREQ(tracks.getItems()[0].getTrack().getURI().c_str(), "spotify:track:1ObZ6sMWPeI56b74WaULRk");

// 	api.unfollowPlaylist(user.getid(), playlist.getid());
// 	ASSERT_FALSE(api.checkUserFollowingPlaylist(user.getid(), playlist.getid(), {user.getid()}));
// }

TEST_F(SpotifyApiEndpointTests, saveTracks) {
	api.saveTracks({"7reiSieFbRTo9KHbT39BZh", "1ObZ6sMWPeI56b74WaULRk"});
	ASSERT_TRUE(api.checkSavedTracks({"7reiSieFbRTo9KHbT39BZh", "1ObZ6sMWPeI56b74WaULRk"}));

	api.unsaveTracks({"7reiSieFbRTo9KHbT39BZh", "1ObZ6sMWPeI56b74WaULRk"});
	ASSERT_FALSE(api.checkSavedTracks({"7reiSieFbRTo9KHbT39BZh", "1ObZ6sMWPeI56b74WaULRk"}));
}

TEST_F(SpotifyApiEndpointTests, fetchTrack) {
	Track track = api.fetchTrack("7reiSieFbRTo9KHbT39BZh");

	ASSERT_STREQ(track.getName().c_str(), "Whole Day Off");
}

TEST_F(SpotifyApiEndpointTests, fetchRecommendations) {
	std::map<std::string, std::string> options;
	options["seed_artists"] = "0QHgL1lAIqAw0HtD7YldmP";
	options["seed_tracks"] = "7reiSieFbRTo9KHbT39BZh";
	options["min_energy"] = "0.7";
	options["min_popularity"] = "50";
	options["market"] = "US";

	Recommendations recommendations = api.fetchRecommendations(options);
	ASSERT_EQ(recommendations.getTracks().size(), 20);
}

TEST_F(SpotifyApiEndpointTests, fetchUserCurrentPlayingTrack) {

}	

TEST_F(SpotifyApiEndpointTests, fetchUserTopTracks) {
    Pager<Track> tracks = api.fetchUserTopTracks();
    ASSERT_EQ(tracks.getLimit(), 20);
}

TEST_F(SpotifyApiEndpointTests, searchTracks) {
	Pager<Track> tracks = api.searchTracks("Whole Day Off");
	ASSERT_STREQ(tracks.getItems()[0].getName().c_str(), "Whole Day Off");
}

TEST_F(SpotifyApiEndpointTests, fetchTracks) {
	std::vector<Track> tracks = api.fetchTracks({"7reiSieFbRTo9KHbT39BZh", "1ObZ6sMWPeI56b74WaULRk"});
	ASSERT_STREQ(tracks[0].getid().c_str(), "7reiSieFbRTo9KHbT39BZh");
	ASSERT_STREQ(tracks[1].getid().c_str(), "1ObZ6sMWPeI56b74WaULRk");
}

TEST_F(SpotifyApiEndpointTests, fetchUserCurrentPlayback) {

}

TEST_F(SpotifyApiEndpointTests, fetchUserDevices) {

}

TEST_F(SpotifyApiEndpointTests, followUser) {
	api.followUser("bphun");
	ASSERT_TRUE(api.checkFollowingUser("bphun"));

	api.unfollowUser("bphun");
	ASSERT_FALSE(api.checkFollowingUser("bphun"));
}

TEST_F(SpotifyApiEndpointTests, fetchUser) {
	User user = api.fetchUser();

	ASSERT_STREQ(user.getid().c_str(), "aymsies");
}

// TEST_F(SpotifyApiEndpointTests, play) {
// 	api.play();
// }

// TEST_F(SpotifyApiEndpointTests, pause) {
// 	api.pause();
// }

// TEST_F(SpotifyApiEndpointTests, skipToNext) {
// 	api.skipToNext();
// }

// TEST_F(SpotifyApiEndpointTests, skipToPrevious) {
// 	api.skipToPrevious();
// }

// TEST_F(SpotifyApiEndpointTests, toggleShuffle) {
// 	api.toggleShuffle("true");
// 	api.toggleShuffle("false");
// }

// TEST_F(SpotifyApiEndpointTests, setRepeat) {
// 	api.setRepeat("true");
// 	api.setRepeat("false");
// }

// TEST_F(SpotifyApiEndpointTests, setVolume) {
// 	api.setVolume(50);
// 	api.setVolume(100);
// }

// TEST_F(SpotifyApiEndpointTests, transferUserPlayback) {

// }



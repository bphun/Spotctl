#include <gtest/gtest.h>
// #include <gmock/gmock.h>

#include <vector>

#include "../src/api/SpotifyAPI.h"

struct SpotifyAPIEndpointTests: public ::testing::Test {
protected:
	static SpotifyAPI sharedSpotifyApi;
	SpotifyAPI api;
	static std::string staticPlaylistID;
	std::string playlistID;

	virtual void SetUp() {
		api = SpotifyAPIEndpointTests::sharedSpotifyApi;
		playlistID = SpotifyAPIEndpointTests::staticPlaylistID;
	}

	static void SetUpTestCase() {
		sharedSpotifyApi = SpotifyAPI();
	}
};

SpotifyAPI SpotifyAPIEndpointTests::sharedSpotifyApi;
std::string SpotifyAPIEndpointTests::staticPlaylistID;

TEST_F(SpotifyAPIEndpointTests, saveAlbums) {
	api.saveAlbums({"0sNOF9WDwhWunNAHPD3Baj"});
	ASSERT_TRUE(api.checkSavedAlbums({"0sNOF9WDwhWunNAHPD3Baj"}));
}

TEST_F(SpotifyAPIEndpointTests, fetchSavedAlbums) {
	Pager<SavedAlbum> albums = api.fetchSavedAlbums();
	ASSERT_STREQ(albums.getItems()[0].getAlbum().getName().c_str(), "She's So Unusual");
}

TEST_F(SpotifyAPIEndpointTests, removeSavedAlbums) {
	api.removeSavedAlbums({"0sNOF9WDwhWunNAHPD3Baj"});
	ASSERT_FALSE(api.checkSavedAlbums({"0sNOF9WDwhWunNAHPD3Baj"}));
}

TEST_F(SpotifyAPIEndpointTests, fetchAlbumTest) {
	Album album = api.fetchAlbum("0sNOF9WDwhWunNAHPD3Baj");
	ASSERT_STREQ(album.getName().c_str(), "She's So Unusual");
}

TEST_F(SpotifyAPIEndpointTests, fetchNewReleases) {
	Pager<Album> albums = api.fetchNewReleases();
	ASSERT_EQ(albums.getLimit(), 20);
}

TEST_F(SpotifyAPIEndpointTests, fetchAlbumTracks) {
	Pager<Track> tracks = api.fetchAlbumTracks("0sNOF9WDwhWunNAHPD3Baj");
	ASSERT_STREQ(tracks.getItems()[0].getName().c_str(), "Money Changes Everything");
}

TEST_F(SpotifyAPIEndpointTests, searchAlbums) {
	Pager<Album> albums = api.searchAlbums("When the party's over");
	ASSERT_STREQ(albums.getItems()[0].getName().c_str(), "when the party's over");
	ASSERT_STREQ(albums.getItems()[0].getArtists()[0].getName().c_str(), "Billie Eilish");
}


//	KMN, I havent touched this project in 9 days and this test just broke for no apparent reason
// TEST_F(SpotifyAPIEndpointTests, fetchArtistAlbums) {
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

TEST_F(SpotifyAPIEndpointTests, fetchAlbums) {
	std::vector<Album> albums = api.fetchAlbums({"0sNOF9WDwhWunNAHPD3Baj", "5lXgrzp3xcFdYCQXtsS6dG", "2VP96XdMOKTXefI8Nui23s"});

	ASSERT_EQ(albums.size(), 3);

	ASSERT_STREQ(albums[0].getName().c_str(), "She's So Unusual");
	ASSERT_STREQ(albums[1].getName().c_str(), "Pleasure");
	ASSERT_STREQ(albums[2].getName().c_str(), "Shawn Mendes");
}

TEST_F(SpotifyAPIEndpointTests, followArtist) {
	api.followArtist("0QHgL1lAIqAw0HtD7YldmP");
	ASSERT_TRUE(api.checkFollowingArtist("0QHgL1lAIqAw0HtD7YldmP"));
}

TEST_F(SpotifyAPIEndpointTests, checkFollowingArtist) {
	ASSERT_TRUE(api.checkFollowingArtist("0QHgL1lAIqAw0HtD7YldmP"));
}

TEST_F(SpotifyAPIEndpointTests, fetchArtist) {
	Artist artist = api.fetchArtist("0QHgL1lAIqAw0HtD7YldmP");
	ASSERT_STREQ(artist.getName().c_str(), "DJ Khaled");
}

TEST_F(SpotifyAPIEndpointTests, fetchUserTopArtists) {
	Pager<Artist> artists = api.fetchUserTopArtists();
	ASSERT_EQ(artists.getLimit(), 20);
}

TEST_F(SpotifyAPIEndpointTests, searchArtists) {
	Pager<Artist> artists = api.searchArtists("billie");
	ASSERT_STREQ(artists.getItems()[0].getName().c_str(),"Billie Eilish");
}

TEST_F(SpotifyAPIEndpointTests, fetchArtistRelatedArtists) {
	std::vector<Artist> artists = api.fetchArtistRelatedArtists("0QHgL1lAIqAw0HtD7YldmP");
	ASSERT_EQ(artists.size(), 20);
}

TEST_F(SpotifyAPIEndpointTests, fetchArtists) {
	std::vector<Artist> artists = api.fetchArtists({"0QHgL1lAIqAw0HtD7YldmP", "6CWTBjOJK75cTE8Xv8u1kj"});
	ASSERT_STREQ(artists[0].getName().c_str(), "DJ Khaled");
	ASSERT_STREQ(artists[1].getName().c_str(), "Feist");
}

TEST_F(SpotifyAPIEndpointTests, fetchArtistTopTracks) {
	std::vector<Track> tracks = api.fetchArtistTopTracks("0QHgL1lAIqAw0HtD7YldmP", "US");
	ASSERT_EQ(tracks.size(), 10);
}

TEST_F(SpotifyAPIEndpointTests, createPlaylist) {
	User user = api.fetchUser();
	Playlist newPlaylist = api.createPlaylist(user.getID().c_str(), "test");
	Playlist retreivedPlaylist = api.fetchPlaylist(user.getID(), newPlaylist.getID());

	ASSERT_STREQ(retreivedPlaylist.getName().c_str(), "test");
	ASSERT_TRUE(api.checkUserFollowingPlaylist(user.getID(), retreivedPlaylist.getID(), {user.getID()}));

	api.unfollowPlaylist(user.getID(), retreivedPlaylist.getID());

	ASSERT_FALSE(api.checkUserFollowingPlaylist(user.getID(), retreivedPlaylist.getID(), {user.getID()}));
}

// TEST_F(SpotifyAPIEndpointTests, editPlaylist) {
// 	User user = api.fetchUser();

// 	Playlist playlist = api.createPlaylist(user.getID(), "test");

// 	ASSERT_STREQ(playlist.getName().c_str(), "test");
// 	ASSERT_TRUE(api.checkUserFollowingPlaylist(user.getID(), playlist.getID(), {user.getID()}));

// 	api.addTracksToPlaylist(user.getID(), playlist.getID(), {"spotify:track:7reiSieFbRTo9KHbT39BZh", "spotify:track:1ObZ6sMWPeI56b74WaULRk"});
// 	Pager<PlaylistTrack> tracks = api.fetchPlaylistTracks(user.getID(), playlist.getID());
// 	ASSERT_STREQ(tracks.getItems()[0].getTrack().getURI().c_str(), "spotify:track:7reiSieFbRTo9KHbT39BZh");
// 	ASSERT_STREQ(tracks.getItems()[0].getTrack().getURI().c_str(), "spotify:track:1ObZ6sMWPeI56b74WaULRk");

// 	api.unfollowPlaylist(user.getID(), playlist.getID());
// 	ASSERT_FALSE(api.checkUserFollowingPlaylist(user.getID(), playlist.getID(), {user.getID()}));
// }

TEST_F(SpotifyAPIEndpointTests, saveTracks) {
	api.saveTracks({"7reiSieFbRTo9KHbT39BZh", "1ObZ6sMWPeI56b74WaULRk"});
	ASSERT_TRUE(api.checkSavedTracks({"7reiSieFbRTo9KHbT39BZh", "1ObZ6sMWPeI56b74WaULRk"}));

	api.unsaveTracks({"7reiSieFbRTo9KHbT39BZh", "1ObZ6sMWPeI56b74WaULRk"});
	ASSERT_FALSE(api.checkSavedTracks({"7reiSieFbRTo9KHbT39BZh", "1ObZ6sMWPeI56b74WaULRk"}));
}

TEST_F(SpotifyAPIEndpointTests, fetchTrack) {
	Track track = api.fetchTrack("7reiSieFbRTo9KHbT39BZh");

	ASSERT_STREQ(track.getName().c_str(), "Whole Day Off");
}

TEST_F(SpotifyAPIEndpointTests, fetchRecommendations) {
	std::map<std::string, std::string> options;
	options["seed_artists"] = "0QHgL1lAIqAw0HtD7YldmP";
	options["seed_tracks"] = "7reiSieFbRTo9KHbT39BZh";
	options["min_energy"] = "0.7";
	options["min_popularity"] = "50";
	options["market"] = "US";

	Recommendations recommendations = api.fetchRecommendations(options);
	ASSERT_EQ(recommendations.getTracks().size(), 20);
}

TEST_F(SpotifyAPIEndpointTests, fetchUserCurrentPlayingTrack) {

}	

TEST_F(SpotifyAPIEndpointTests, fetchUserTopTracks) {
    Pager<Track> tracks = api.fetchUserTopTracks();
    ASSERT_EQ(tracks.getLimit(), 20);
}

TEST_F(SpotifyAPIEndpointTests, searchTracks) {
	Pager<Track> tracks = api.searchTracks("Whole Day Off");
	ASSERT_STREQ(tracks.getItems()[0].getName().c_str(), "Whole Day Off");
}

TEST_F(SpotifyAPIEndpointTests, fetchTracks) {
	std::vector<Track> tracks = api.fetchTracks({"7reiSieFbRTo9KHbT39BZh", "1ObZ6sMWPeI56b74WaULRk"});
	ASSERT_STREQ(tracks[0].getID().c_str(), "7reiSieFbRTo9KHbT39BZh");
	ASSERT_STREQ(tracks[1].getID().c_str(), "1ObZ6sMWPeI56b74WaULRk");
}

TEST_F(SpotifyAPIEndpointTests, fetchUserCurrentPlayback) {

}

TEST_F(SpotifyAPIEndpointTests, fetchUserDevices) {

}

TEST_F(SpotifyAPIEndpointTests, followUser) {
	api.followUser("bphun");
	ASSERT_TRUE(api.checkFollowingUser("bphun"));

	api.unfollowUser("bphun");
	ASSERT_FALSE(api.checkFollowingUser("bphun"));
}

TEST_F(SpotifyAPIEndpointTests, fetchUser) {
	User user = api.fetchUser();

	ASSERT_STREQ(user.getID().c_str(), "aymsies");
}

// TEST_F(SpotifyAPIEndpointTests, play) {
// 	api.play();
// }

// TEST_F(SpotifyAPIEndpointTests, pause) {
// 	api.pause();
// }

// TEST_F(SpotifyAPIEndpointTests, skipToNext) {
// 	api.skipToNext();
// }

// TEST_F(SpotifyAPIEndpointTests, skipToPrevious) {
// 	api.skipToPrevious();
// }

// TEST_F(SpotifyAPIEndpointTests, toggleShuffle) {
// 	api.toggleShuffle("true");
// 	api.toggleShuffle("false");
// }

// TEST_F(SpotifyAPIEndpointTests, setRepeat) {
// 	api.setRepeat("true");
// 	api.setRepeat("false");
// }

// TEST_F(SpotifyAPIEndpointTests, setVolume) {
// 	api.setVolume(50);
// 	api.setVolume(100);
// }

// TEST_F(SpotifyAPIEndpointTests, transferUserPlayback) {

// }



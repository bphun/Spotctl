#ifndef SPOTIFYCLI_H
#include "SpotifyClient.h"
#endif

int main() {
	// viewManager.presentView(authenticationViewIdentifier);
	// viewManager.refreshView(authenticationViewIdentifier);
	SpotifyAPI api;
	SocketUtils socketUtils("guc3-accesspoint-b-sh25.ap.spotify.com", 4070);

	socketUtils.connectToHost();

	// CurlUtils curlUtils;

	// Album album = api.fetchAlbum("5lXgrzp3xcFdYCQXtsS6dG");

	// for (Track track : album.getTracks().getItems()) {
	// 	printf("%s\n", track.getURI().c_str());
	// }

	// Track track = api.fetchTrack("0CZ8lquoTX2Dkg7Ak2inwA");

	// printf("%s\n", track.getHref().c_str());

	// Playlist playlist = api.createPlaylist(user.getID(), "test");

	// api.addTracksToPlaylist(user.getID(), playlist.getID(), {"spotify:track:7reiSieFbRTo9KHbT39BZh", "spotify:track:1ObZ6sMWPeI56b74WaULRk"});
	// Pager<PlaylistTrack> tracks = api.fetchPlaylistTracks(user.getID(), playlist.getID());

	// api.unfollowPlaylist(user.getID(), playlist.getID());
 	// viewManager.presentView(playerViewIdentifier);
	// viewManager.refreshView(playerViewIdentifier);

	// init();
	// WINDOW* loginWindow = newwin(10, 36,( (screenHeight / 2) - 5) - 10, (screenWidth / 2) - 13);

	// box(loginWindow, 0, 0);

	// getmaxyx(loginWindow, loginWindowHeight, loginWindowWidth);

	// prompt(loginWindow, (loginWindowWidth / 2) - 4, 0, loginPrompt);
	// prompt(loginWindow, loginWindowWidth / 10, loginWindowHeight / 5, emailPrompt);
	// // wgetstr(loginWindow, email);

	// prompt(loginWindow, loginWindowWidth / 10, loginWindowHeight / 4, passwordPrompt);
	// // wgetstr(loginWindow, password);

	// refresh();
	// wrefresh(loginWindow);

	// deinit();

	return 0;
}

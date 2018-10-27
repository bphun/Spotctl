#ifndef SPOTIFYCLI_H
#include "SpotifyClient.h"
#endif

int main() {
	// viewManager.presentView(authenticationViewIdentifier);
	// viewManager.refreshView(authenticationViewIdentifier);
	SpotifyAPI api;

	User user = api.fetchUser();

	printf("%s\n", user.getID().c_str());

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

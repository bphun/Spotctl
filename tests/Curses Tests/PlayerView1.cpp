#include <vector>
#include <string>
#include <stdio.h> 
#include <sstream>
#include <thread>
#include <chrono>

#include "View.h"
#include "../Constants.h"
#include "../MediaPlayer/MediaPlayer.h"

class PlayerView: public View {

private:
// int terminalScreenWidth, terminalScreenHeight;

	WINDOW* sidebarSubwindow;
	WINDOW* mediaControllerWindow;

	MediaPlayer* mediaPlayer;

	// char progressString[] = "[==============================                              ] 2:30 of 5:00"; 
	char* progressString = strdup("");

	void displaySideBarWindow() {
		sidebarSubwindow = subwin(parentWindow, 
		                          terminalScreenHeight, 
		                          playerViewSideBarWidth, 
		                          0, 
		                          0);
		box(sidebarSubwindow, 0, 0);

		prompt(sidebarSubwindow, (playerViewSideBarWidth / 2) - (playerViewSideBarWidth / 5), 0, playlistsSideBarTitle);		

		std::thread sideBarUpdateThread(&PlayerView::updateSidebar, this);

		sideBarUpdateThread.join();
	}

	void displayMediaControllerWindow() {
		mediaControllerWindow = subwin(parentWindow, playerViewMediaControllerHeight, 
		                        terminalScreenWidth - playerViewSideBarWidth, 
		                        (terminalScreenHeight - playerViewMediaControllerHeight), 
		                        playerViewSideBarWidth);

		box(mediaControllerWindow, 0, 0);

		// updateSidebar();

		std::thread progressBarThread(&PlayerView::progressBarUpdate, this);
		// startProgressBar();
		// printf("%d\n", 60 * (220 / 224));
		// displayKeyCommands();
		progressBarThread.join();
		//►
	}

	void updateSidebar() {

		// keypad(sidebarSubwindow, true);

		// int key;
		// int highlight = 0;

		// while (true) {
		// 	std::vector<std::string> playlists;
		// 	playlists = spotifyAPI.fetchUserPlaylists();
		// 	int y = 1;

		// 	for (size_t i = 0; i < playlists.size(); i++) {
		// 		char* playlist = strdup(""); 
		// 		strcpy(playlist, playlists[i].c_str());

		// 		if (i == highlight) { wattron(sidebarSubwindow, A_REVERSE); }
		// 		prompt(sidebarSubwindow, 2, y, playlist);
		// 		wattroff(sidebarSubwindow, A_REVERSE);

		// 		y++;
		// 	}
		// 	key = wgetch(sidebarSubwindow);

		// 	switch (key) {
		// 		case KEY_UP:
		// 			if (highlight == 0) { break; }
		// 			highlight--;
		// 			break;
		// 		case KEY_DOWN:
		// 			if (highlight == playlists.size() - 1) { break; }
		// 			highlight++;
		// 			break;
		// 	}

		// 	std::this_thread::sleep_for(std::chrono::milliseconds(5));
		// 	refresh();
		// }
	}

	void progressBarUpdate() {
		while (true) { 
			strcpy(progressString, newProgressBarString().c_str());
			prompt(mediaControllerWindow, 
			       ((terminalScreenWidth - playerViewSideBarWidth) / 2) - (playerViewMediaControllerProgressBarStringLength / 2), 
			       ((playerViewMediaControllerHeight) / 2), 
			       progressString);

			// displayCurrentSongInfo

			refresh();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		// char progressString[] = "[==============================                              ] 2:30 of 5:00";
		/*prompt(mediaControllerWindow, 
		       ((terminalScreenWidth - playerViewSideBarWidth) / 2) - (playerViewMediaControllerProgressBarStringLength / 2), 
		       (playerViewMediaControllerHeight) / 2,
		        progressString);*/
	}

	std::string newProgressBarString() {
		double songDuration = mediaPlayer->currentSongDuration();
		double currentPosition = mediaPlayer->currentSongPosition();

		int numEqualSigns = playerViewMediaControllerProgressBarMaxNumEqualSigns * (currentPosition / songDuration);

		int positionMinutes = currentPosition / 60;
		int positionSeconds = ((int)currentPosition) % 60;

		int durationMinutes = songDuration / 60;
		int durationSeconds = ((int)songDuration) % 60;

		std::stringstream progressString;

		progressString << "[";

		for (int e = 0; e < numEqualSigns; e++) { 
			progressString << "=";
		}

		for (int s = 0; s < playerViewMediaControllerProgressBarMaxNumEqualSigns - numEqualSigns; s++) { 
			progressString << " "; 
		}

		progressString << "] " << positionMinutes << ":" << positionSeconds << " of ";
		progressString << durationMinutes << ":" << durationSeconds;

		return progressString.str();
		// return "[==============================                              ] 2:30 of 5:00";
	}

	void displayMainWindow(std::string identifier) {
	}

public:

	PlayerView(int terminalScreenWidth, int terminalScreenHeight) {
		View::terminalScreenWidth = terminalScreenWidth;
		View::terminalScreenHeight = terminalScreenHeight;

		mediaPlayer = new MediaPlayer(spotifyAPI);
	}

	void initialize() override {
		curs_set(false);

		parentWindow = newwin(terminalScreenHeight, terminalScreenWidth, 0, 0);

		// std::thread sidebarThread(&PlayerView::displaySideBarWindow, this);
		// displaySideBarWindow();
		displayMediaControllerWindow();

		// std::thread updateThread(&PlayerView::updateUI, this);

		// updateThread.join();

		// sidebarThread.join();
	}

	void refresh() override {
		wrefresh(parentWindow);
	}

};
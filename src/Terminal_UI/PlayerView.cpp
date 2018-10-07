#include <vector>
#include <string>
#include <stdio.h> 
#include <sstream>
#include <thread>
#include <chrono>
#include <Panel.h>

#include "View.h"
#include "../Constants.h"
#include "../MediaPlayer/MediaPlayer.h"

class PlayerView: public View {

private:
	WINDOW* windows[2];	//	0: sidebarSubwindow, 1: mediaControllerWindow
	PANEL* panels[2];

	PANEL* active;
	int ch;
	char* progressString = strdup("");

	MediaPlayer* mediaPlayer;

	void initializeWindows() {
		windows[0] = subwin(parentWindow, 
		                          terminalScreenHeight, 
		                          playerViewSideBarWidth, 
		                          0, 
		                          0);
		box(windows[0], 0, 0);
		prompt(windows[0], (playerViewSideBarWidth / 2) - (playerViewSideBarWidth / 5), 0, playlistsSideBarTitle);
		keypad(windows[0], true);

		windows[1] = subwin(parentWindow, playerViewMediaControllerHeight, 
		                        terminalScreenWidth - playerViewSideBarWidth, 
		                        (terminalScreenHeight - playerViewMediaControllerHeight), 
		                        playerViewSideBarWidth);
		box(windows[1], 0, 0);

	}

	void initializePanels() {
		panels[0] = new_panel(windows[0]);
		panels[1] = new_panel(windows[1]);
	}

	void displaySidebarContents(int key) {
		int highlight = 0;

		std::vector<std::string> playlists;
		spotifyAPI.fetchUserPlaylists(playlists);
		int y = 1;

		// printf("%lu\n", playlists.size());

		switch (key) {
			case KEY_UP:
			if (highlight == 0) { break; }
			highlight--;
			break;
			case KEY_DOWN:
			if (highlight == playlists.size() - 1) { break; }
			highlight++;
			break;
		}

		// print

		for (size_t i = 0; i < playlists.size(); i++) {
			char* playlist = strdup(""); 
			strcpy(playlist, playlists[i].c_str());

			if (i == highlight) { wattron(windows[0], A_REVERSE); }
			prompt(windows[0], 2, y, playlist);
			wattroff(windows[0], A_REVERSE);

			y++;
		}
	}

	void displayMediaPlayerContents() {
		strcpy(progressString, newProgressBarString().c_str());
		prompt(windows[1], 
		       ((terminalScreenWidth - playerViewSideBarWidth) / 2) - (playerViewMediaControllerProgressBarStringLength / 2), 
		       ((playerViewMediaControllerHeight) / 2), 
		       progressString);
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


public:

	PlayerView(int terminalScreenWidth, int terminalScreenHeight) {
		View::terminalScreenWidth = terminalScreenWidth;
		View::terminalScreenHeight = terminalScreenHeight;

		mediaPlayer = new MediaPlayer(spotifyAPI);
	}

	void initialize() override {
		parentWindow = newwin(terminalScreenHeight, terminalScreenWidth, 0, 0);

		start_color();
		curs_set(false);
		noecho();
		keypad(stdscr, TRUE);

		initializeWindows();
		initializePanels();

		displaySidebarContents(0);
		displayMediaPlayerContents();

		set_panel_userptr(panels[0], panels[1]);
		set_panel_userptr(panels[1], panels[0]);

		update_panels();
		doupdate();

		active = panels[1];
		while ((ch = getch()) != KEY_F(1)) {
			if (active == panels[0]) {	//	Sidebar controlls
				switch (ch) {
					case KEY_UP:
					case KEY_DOWN:
					if (active != panels[0]) { break; }
					displaySidebarContents(ch);
					break;
				}
			}

			switch (ch) {	//	Select active window using tab
				case 9:
					wattroff(panel_window(active), A_REVERSE);
					box(panel_window(active), 0, 0);

					active = (PANEL*)panel_userptr(active);
					top_panel(active);

					wattron(panel_window(active), A_REVERSE);
					box(panel_window(active), 0, 0);
					prompt(windows[0], (playerViewSideBarWidth / 2) - (playerViewSideBarWidth / 5), 0, playlistsSideBarTitle);
					wattroff(panel_window(active), A_REVERSE);
			}

			if (active == panels[1]) {	//	Media player controls
				switch (ch) {

				}
			}

			update_panels();
			doupdate();
		}
	}

	void refresh() override {
		wrefresh(parentWindow);
	}

};
#include "PlayerView.h"

void PlayerView::initializeWindows() {
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

void PlayerView::initializePanels() {
	panels[0] = new_panel(windows[0]);
	panels[1] = new_panel(windows[1]);
}

void PlayerView::displaySidebarContents(int key) {
	int highlight = 0;

	 std::vector<Playlist> playlists = spotifyApi.fetchUserPlaylists().getItems();

	int y = 1;
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

	for (size_t i = 0; i < playlists.size(); i++) {
		if (i == highlight) { wattron(windows[0], A_REVERSE); }
		prompt(windows[0], 2, y, playlists[i].getName().c_str());
		wattroff(windows[0], A_REVERSE);

		y++;
	}
}

void PlayerView::displayMediaPlayerContents() {
	strcpy(progressString, newProgressBarString().c_str());
	prompt(windows[1], 
	       ((terminalScreenWidth - playerViewSideBarWidth) / 2) - (playerViewMediaControllerProgressBarStringLength / 2), 
	       ((playerViewMediaControllerHeight) / 2), 
	       progressString);
}

std::string PlayerView::newProgressBarString() {
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
}

PlayerView::PlayerView(int terminalScreenWidth, int terminalScreenHeight) {
	View::terminalScreenWidth = terminalScreenWidth;
	View::terminalScreenHeight = terminalScreenHeight;

	mediaPlayer = new MediaPlayer(spotifyApi);
}

void PlayerView::initialize() {
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
		break;
	}

	if (active == panels[1]) {	//	Media player controls
		switch (ch) {

		}
	}

	update_panels();
	doupdate();
}
}

void PlayerView::refresh() {
	wrefresh(parentWindow);
}


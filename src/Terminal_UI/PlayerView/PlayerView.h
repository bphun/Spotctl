#include <vector>
#include <string>
#include <stdio.h> 
#include <sstream>
#include <thread>
#include <chrono>
#include <Panel.h>

#include "../View.h"
#include "../../Constants.h"
#include "../../MediaPlayer/MediaPlayer.h"

class PlayerView: public View {

private:
	WINDOW* windows[2];	//	0: sidebarSubwindow, 1: mediaControllerWindow
	PANEL* panels[2];

	PANEL* active;
	int ch;
	char* progressString = strdup("");

	MediaPlayer* mediaPlayer;

	void initializeWindows();
	void initializePanels();
	void displaySidebarContents(int key);
	void displayMediaPlayerContents();

	std::string newProgressBarString();


public:

	PlayerView(int terminalScreenWidth, int terminalScreenHeight);

	void initialize() override;
	void refresh() override;

};
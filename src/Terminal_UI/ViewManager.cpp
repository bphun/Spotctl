#include "ViewManager.h"
#include <stdio.h>

ViewManager::ViewManager() {
	init();
}

ViewManager::~ViewManager() {
	views.clear();
	deinit();
}

void ViewManager::init() {
	initscr();
	cbreak();
	keypad(stdscr, TRUE);

	getmaxyx(stdscr, terminalScreenHeight, terminalScreenWidth);

}

void ViewManager::deinit() {
	getch();
	endwin();
}

void ViewManager::presentView(std::string viewIdentifier) {
	clear();
	if (views.find(viewIdentifier) == views.end()) {
		if (viewIdentifier.compare(authenticationViewIdentifier) == 0) {
			views[viewIdentifier] = new AuthenticationView(terminalScreenWidth, terminalScreenHeight);
		} else if (viewIdentifier.compare(playerViewIdentifier) == 0) {
			views[viewIdentifier] = new PlayerView(terminalScreenWidth, terminalScreenHeight);
		}	/*	Add in statements for other views 	*/
	}
	views[viewIdentifier]->initialize();
	refresh();
}

void ViewManager::refreshView(std::string viewIdentifier) {
	views[viewIdentifier]->refresh();
}

void ViewManager::deinitializeView(std::string viewIdentifier) {
	views.erase(viewIdentifier);
}

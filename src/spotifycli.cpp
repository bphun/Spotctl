#include "Spotifycli.h"

void init() {
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	// noecho();

	getmaxyx(stdscr, screenHeight, screenWidth);
}

void deinit() {
	getch();
	endwin();
}

void prompt(WINDOW* window, unsigned int x, unsigned int y, const char* str) {
	mvwprintw(window, y, x, str);
}

int main() {
	// viewManager.presentView(authenticationViewIdentifier);
	// viewManager.refreshView(authenticationViewIdentifier);

	viewManager.presentView(playerViewIdentifier);
	viewManager.refreshView(playerViewIdentifier);

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

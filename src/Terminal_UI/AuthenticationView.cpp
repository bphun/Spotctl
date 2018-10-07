#include "View.h"
#include "../Constants.h"

class AuthenticationView: public View {
private:

	char email[64];
	char password[64];

	bool userAuthenticated;

	void presentEmailView() {
		box(parentWindow, 0, 0);
		prompt(parentWindow, (authenticationViewInputFrameWidth / 2) - 4, 0, loginPrompt);
		prompt(parentWindow, authenticationViewInputFrameWidth / 10, authenticationViewInputFrameHeight / 5, emailPrompt);
		wgetstr(parentWindow, email);
		if (email[0] == 0) { 
			clear();
			presentEmailView();
		}
	}

	void presentPasswordView() {
		box(parentWindow, 0, 0);
		prompt(parentWindow, (authenticationViewInputFrameWidth / 2) - 4, 0, loginPrompt);
		prompt(parentWindow, authenticationViewInputFrameWidth / 10, authenticationViewInputFrameHeight / 4, passwordPrompt);
		wgetstr(parentWindow, password);
		if (password[0] == 0) { 
			clear();
			presentPasswordView();
		}
	}

	void authenticateUser(char email[], char password[]) {
		userAuthenticated = spotifyAPI.authenticateUser(email, password);
	}

public:
	AuthenticationView(int terminalScreenWidth, int terminalScreenHeight) {
		View::terminalScreenWidth = terminalScreenWidth;
		View::terminalScreenHeight = terminalScreenHeight;
	}

	void initialize() override {
		parentWindow = newwin(authenticationViewInputFrameHeight, 
		                     authenticationViewInputFrameWidth,
		                     (View::terminalScreenHeight / 2) - (authenticationViewInputFrameHeight / 2), 
		                     (View::terminalScreenWidth / 2) - (authenticationViewInputFrameWidth / 2));
		
		while (!userAuthenticated) {
			presentEmailView();

			wclear(parentWindow);

			presentPasswordView();

			authenticateUser(email, password);
		}

		wclear(parentWindow);
	}

	void refresh() override {
		wrefresh(parentWindow);
	}

};
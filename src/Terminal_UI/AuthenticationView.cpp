#include "View.h"
#include "../Constants.h"

class AuthenticationView: public View {
private:
	// int loginWindowWidth, authenticationViewInputFrameHeight;
	// string email, password;
	char email[64];
	char password[64];
	// int terminalScreenWidth, terminalScreenHeight;

	bool userAuthenticated;

	void presentEmailView() {
		box(window, 0, 0);
		prompt(window, (authenticationViewInputFrameWidth / 2) - 4, 0, loginPrompt);
		prompt(window, authenticationViewInputFrameWidth / 10, authenticationViewInputFrameHeight / 5, emailPrompt);
		wgetstr(window, email);
		if (email[0] == 0) { 
			clear();
			presentEmailView();
		}
	}

	void presentPasswordView() {
		box(window, 0, 0);
		prompt(window, (authenticationViewInputFrameWidth / 2) - 4, 0, loginPrompt);
		prompt(window, authenticationViewInputFrameWidth / 10, authenticationViewInputFrameHeight / 4, passwordPrompt);
		wgetstr(window, password);
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
		window = newwin(authenticationViewInputFrameHeight, 
		                     authenticationViewInputFrameWidth,
		                     (View::terminalScreenHeight / 2) - (authenticationViewInputFrameHeight / 2), 
		                     (View::terminalScreenWidth / 2) - (authenticationViewInputFrameWidth / 2));
		
		while (!userAuthenticated) {
			presentEmailView();

			wclear(window);

			presentPasswordView();

			authenticateUser(email, password);
		}

		wclear(window);
	}

	void refresh() override {
		wrefresh(window);
	}

};
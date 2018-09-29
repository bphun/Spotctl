#include "View.h"
#include "../Constants.h"

class PlayerView: public View {

private:
// int terminalScreenWidth, terminalScreenHeight;

public:

	PlayerView(int terminalScreenWidth, int terminalScreenHeight) {
		View::terminalScreenWidth = terminalScreenWidth;
		View::terminalScreenHeight = terminalScreenHeight;
	}

	void initialize() override {
		window = newwin(terminalScreenHeight, terminalScreenWidth, 0, 0);

		displaySideBarBox();
		displayScrubberBox();
		// display()
	}

	void refresh() override {
		wrefresh(window)
	}

};
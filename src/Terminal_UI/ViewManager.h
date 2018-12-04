#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include "View.h"
#include "PlayerView/PlayerView.h"
#include "../Constants.h"
// #include "AuthenticationView.cpp"

#include <map>
#include <string.h>

class ViewManager {

private:
	std::map<std::string, View*> views;

	int terminalScreenWidth, terminalScreenHeight;
	
public:
	ViewManager();
	~ViewManager();

	void init();
	void deinit();

	void presentView(std::string viewIdentifier);
	void refreshView(std::string viewIdentifier);
	void deinitializeView(std::string viewIdentifier);
};

#endif

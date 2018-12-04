#ifndef SPOTIFYCLI_H
#define SPOTIFYCLI_H

#include <string>
#include <iostream>
#include <ncurses.h>

#include "api/SpotifyAPI.h"

#include "Constants.h"
#include "Terminal_UI/ViewManager.h"

#include "api/utils/json.h"
#include "api/utils/sockets/SocketUtils.h"

// ViewManager viewManager;

unsigned int screenWidth;
unsigned int screenHeight;

unsigned int loginWindowWidth;
unsigned int loginWindowHeight;

char email[64];
char password[64];

#endif
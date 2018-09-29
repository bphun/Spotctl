#ifndef SPOTIFYCLI_H
#define SPOTIFYCLI_H

#include <iostream>
#include <ncurses.h>
#include <string>

#include "Constants.h"
#include "Terminal_UI/ViewManager.h"

ViewManager viewManager;

unsigned int screenWidth;
unsigned int screenHeight;

unsigned int loginWindowWidth;
unsigned int loginWindowHeight;

char email[64];
char password[64];

#endif
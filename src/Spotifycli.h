#ifndef SPOTIFYCLI_H
#define SPOTIFYCLI_H

#include <iostream>
#include <ncurses.h>
#include <string>
// #include <spotify-api-plusplus/SpotifyAPI.h>
#include "../include/spotifyapi/SpotifyAPI.h"
#include "Constants.h"

unsigned int screenWidth;
unsigned int screenHeight;

unsigned int loginWindowWidth;
unsigned int loginWindowHeight;

char email[64];
char password[64];

#endif
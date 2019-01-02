#ifndef SPOTIFYCLI_H
#define SPOTIFYCLI_H

#include <iostream>
#include <readline/history.h>
#include <readline/readline.h>

#include "api/SpotifyApi.h"

typedef std::map<std::string, std::string> options_t;

void displayHelpDialogue(bool unknownArgs);
void enterInteractiveMode(SpotifyApi api);
void parseArguments(SpotifyApi api, int argc, char* argv[]);
void executeRequest(SpotifyApi api, char* request);

#endif
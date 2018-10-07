#ifndef CONSTANTS_H
#define CONSTANTS_H

//	UI Constants
const int authenticationViewInputFrameWidth = 50;
const int authenticationViewInputFrameHeight = 10;

const int playerViewSideBarWidth = 25;
const int playerViewMediaControllerHeight = 7;
const int playerViewMediaControllerProgressBarStringLength = 80;
const int playerViewMediaControllerProgressBarMaxNumEqualSigns = 80;
const int playerViewKeyCommandWindowHeight = 2;

//	User Authentication View Prompts
const char loginPrompt[] = " Login ";
const char emailPrompt[] = "Email: ";
const char passwordPrompt[] = "Password: ";

//	Player View Prompts
const char playlistsSideBarTitle[] = " Playlists ";
const char mediaControllerPlayPrompt[] = "(P)lay";
const char mediaControllerNextPrompt[] = "(N)ext";
const char mediaControllerPausePrompt[] = "(P)ause";
const char mediaControllerRewindPrompt[] = "(R)ewind";
const char mediaControllerHelpPrompt[] = "(H)elp";

//	View Identifiers
const std::string playerViewIdentifier = "playerview";
const std::string authenticationViewIdentifier = "authview";

//	View Manager constants
const int numViews = 2;

#endif
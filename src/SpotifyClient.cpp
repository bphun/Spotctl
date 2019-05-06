#ifndef SPOTIFYCLI_H
#include "SpotifyClient.h"
#endif

int main(int argc, char* argv[]) {
	if (argc > 1) {
		SpotifyApi api;

		if (!api.userAuthenticated()) {
			printf("You have not yet authorized this application to access your spotify account.\n");
			authenticateUser(api);
		}

		parseArguments(api, argc, argv);

		// runCommand();

	} else {
		displayHelpDialogue(false);
	}

	return 0;
}

void authenticateUser(SpotifyApi api) {
	std::string authorizationCode = "";
	printf("Please visit this link (https://bit.ly/2FXCr7i) and copy/paste the text seen in the browser once you've been redirected below\n");
	std::cin >> authorizationCode;
	while (authorizationCode == "") {
		printf("You did not enter an authorization code\n");
		std::cin >> authorizationCode;
	}
	api.authenticateSpotifyUser(authorizationCode);

	std::string username = "";
	std::string password = "";
	std::string confirmedPassword = "";

	printf("Please login to your Spotify client account. If you do not have an account, press your escape key.\n");

	while (username.empty() && password.empty()) {
		printf("Username: ");
		std::cin >> username;

		printf("Password: ");
		std::cin >> password;

		printf("Confirm Password: ");
		std::cin >> confirmedPassword;
	}

	while (confirmedPassword != password) {
		printf("The two passwords you entered do not match.\n");
		printf("Password: ");
		std::cin >> password;

		printf("Confirm Password: ");
		std::cin >> confirmedPassword;
	}

	api.createClientUser(username, password);
}

void parseArguments(SpotifyApi api, int argc, char* argv[]) {
	if (strcmp(argv[1], "play") == 0) {
		if (argc == 3) {
			options_t options;
			options["context_uri"] = argv[2];
			api.play(options);
		} else {
			api.play();
		}
	} else if (strcmp(argv[1], "pause") == 0) {
		api.pause();
	} else if (strcmp(argv[1], "next") == 0) {
		api.skipToNext();
	} else if (strcmp(argv[1], "previous") == 0) {
		api.skipToPrevious();
	} else if (strcmp(argv[1], "shuffle") == 0) {
		if (argc == 3) {
			api.toggleShuffle(atoi(argv[2]));
		} else {
			displayHelpDialogue(true);
		}
	} else if (strcmp(argv[1], "repeat") == 0) {
		if (argc == 3) {
			api.setRepeat(std::string(argv[2]));
		} else {
			displayHelpDialogue(true);
		}
	} else if (strcmp(argv[1], "view") == 0) {
		std::cout << argc << std::endl;
		if (argc == 4) {

			Pager<Album> albums = api.searchAlbums(argv[3]);
			for (Album a : albums.getItems()) {
				printf("%s %s\n", a.getArtists()[0].getName().c_str(), a.getName().c_str());
				// std::cout << a.getArtists()[0] << " " << a.getName() << std::endl;
				// std::cout << a.getArtists()[0] << " " << a.getName() << std::endl;
			}
		} else {
			displayHelpDialogue(true);
		}
	} else if (strcmp(argv[1], "help") == 0) {
		displayHelpDialogue(false);
	} else if (strcmp(argv[1], "logout") == 0) {
		api.logout();
	} else if (strcmp(argv[1], "status") == 0) {
		CurrentlyPlayingContext status = api.fetchUserCurrentPlayback();
		printf("%s\n", status.getAlbum().getName().c_str());
	} else if (strcmp(argv[1], "login") == 0) {
		authenticateUser(api);
	} else {
		displayHelpDialogue(true);
	}
}

void displayHelpDialogue(bool unknownArgs) {
	if (unknownArgs) {
		printf("Unknown arguments were provided\n");
	}
	printf("Usage: spotifyClient <arg-name> [options]\n\t");
	printf("play\t\tContinues playback of the current playing song\n\t"/* or begins playing a desired specified album, artist, or playlist\n\t"*/);
	printf("pause\t\tPauses the current playing track\n\t");
	printf("next\t\tSkips to the next song in the play queue\n\t");
	printf("previous\tRewinds to the previous song in the play queue\n\t");
	printf("shuffle \tSets shuffle to the specified mode (1: on, 0: off)\n\t");
	printf("view\t\t[item] View a playlist, song, artist, or album\n\t");
	printf("login\t\tSign in to your spotify account\n\t");
	printf("loop\t\tSets repeat to the specified mode (track, context, off)\n\t");
	printf("logout\t\tLogout of your spotify account\n\t");
	// printf("--status\t\tView current status of your listening session\n\t");
	printf("help\t\tDisplays the help dialogue\n");
}


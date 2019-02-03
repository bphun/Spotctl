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

		if (strcmp(argv[0], "-i") == 0 || strcmp(argv[0], "--interactive") == 0) {
			enterInteractiveMode(api);
			return 0;
		}
		parseArguments(api, argc, argv);
	} else {
		displayHelpDialogue(false);
	}

	return 0;
}

void authenticateUser(SpotifyApi api) {
	std::string authorizationCode = "";
	printf("Please visit this link (https://bit.ly/2AvyAeq) and copy/paste the text seen in the browser once you've been redirected below\n");
	std::cin >> authorizationCode;
	while (authorizationCode == "") {
		printf("You did not enter an authorization code\n");
		std::cin >> authorizationCode;
	}

	api.authenticateUser(authorizationCode);
}

void enterInteractiveMode(SpotifyApi api) {
	while (1) {
		char* line = readline("> ");
		if(!line) {
			break;
		}
		if(*line) { add_history(line); }

		executeRequest(api, line);

		free(line);
	}
}

void parseArguments(SpotifyApi api, int argc, char* argv[]) {
	if (strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "--play") == 0) {
		if (argc == 3) {
			options_t options;
			options["context_uri"] = argv[2];
			api.play(options);
		} else {
			api.play();
		}
	} else if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--stop") == 0) {
		api.pause();
	} else if (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "--next") == 0) {
		api.skipToNext();
	} else if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "--rewind") == 0) {
		api.skipToPrevious();
	} else if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "--mix") == 0) {
		if (argc == 3) {
			switch (atoi(argv[2])) {
				case 0:
				api.toggleShuffle(false);
				break;
				case 1:
				api.toggleShuffle(true);
				break;
			}
		} else {
			displayHelpDialogue(true);
		}
	} else if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--loop") == 0) {
		if (argc == 3) {
			api.setRepeat(std::string(argv[2]));
		} else {
			displayHelpDialogue(true);
		}
	} else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		displayHelpDialogue(false);
	} else if (strcmp(argv[1], "--logout") == 0) {
		api.logout();
	} else if (strcmp(argv[1], "--status") == 0) {
		CurrentlyPlayingContext status = api.fetchUserCurrentPlayback();
		printf("%s\n", status.getAlbum().getName().c_str());
	} else if (strcmp(argv[1], "--authenticate") == 0) {
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
	printf("-p, --play\t\tContinues playback of the current playing song\n\t"/* or begins playing a desired specified album, artist, or playlist\n\t"*/);
	printf("-s, --stop\t\tPauses the current playing track\n\t");
	printf("-n, --next\t\tSkips to the next song in the play queue\n\t");
	printf("-r, --rewind\t\tRewinds to the previous song in the play queue\n\t");
	printf("-m, --mix \t\tSets shuffle to the specified mode (1: on, 0: off)\n\t");
	printf("-l, --loop\t\tSets repeat to the specified mode (track, context, off)\n\t");
	// printf("-i, --interactive       Enter an interactive mode with enhanced graphics\n\t");
	printf("--logout\t\tLogout\n\t");
	printf("--authenticate\t\tSign in to your spotify account\n\t");
	// printf("--status\t\tView current status of your listening session\n\t");
	printf("-h, --help\t\tDisplays the help dialogue\n");
}


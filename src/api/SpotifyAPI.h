#ifndef SPOTIFY_API_H
#define SPOTIFY_API_H

class SpotifyAPI {

private:

public:
	SpotifyAPI();
	~SpotifyAPI();

	bool authenticateUser(char email[], char password[]);

};

#endif

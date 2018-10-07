#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H

#include <string>

#include "../api/SpotifyAPI.h"

class MediaPlayer {
private:

	bool playing;
	SpotifyAPI spotifyAPI;
	double duration, position;	//	in seconds
	std::string streamURL, currSongId;

public:
	MediaPlayer(SpotifyAPI spotifyAPI);
	MediaPlayer(SpotifyAPI spotifyAPI, std::string streamURL);
	~MediaPlayer();

	void play();
	void pause();
	void setSong(std::string id);
	void scrubToPosition(double position);

	double currentSongDuration();
	double currentSongPosition();

	bool isPlaying();
	bool isPaused();

};

#endif
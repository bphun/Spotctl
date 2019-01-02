#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H

#include <string>

#include "../api/SpotifyApi.h"

class MediaPlayer {
private:

	bool playing;
	SpotifyApi spotifyApi;
	double duration, position;	//	in seconds
	std::string streamURL, currSongId;

public:
	MediaPlayer(SpotifyApi spotifyAPI);
	MediaPlayer(SpotifyApi spotifyAPI, std::string streamURL);
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
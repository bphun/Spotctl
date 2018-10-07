#include "MediaPlayer.h"

MediaPlayer::MediaPlayer(SpotifyAPI spotifyAPI) {
	this->spotifyAPI = spotifyAPI;

	this->duration = 223.0;
	this->position = 220.0;
}

MediaPlayer::MediaPlayer(SpotifyAPI spotifyAPI, std::string streamURL) {
	this->spotifyAPI = spotifyAPI;
	this->streamURL = streamURL;
}

MediaPlayer::~MediaPlayer() {

}

void MediaPlayer::play() {
	playing = true;

}

void MediaPlayer::pause() {
	playing = false;
}

void MediaPlayer::setSong(std::string id) {
	this->currSongId = id;
}

void MediaPlayer::scrubToPosition(double position) {
	this->position = position;
}

double MediaPlayer::currentSongDuration() {
	return duration;
}

double MediaPlayer::currentSongPosition() {
	return position;
}

bool MediaPlayer::isPlaying() {
	return playing;
}

bool MediaPlayer::isPaused() {
	return !playing;
}
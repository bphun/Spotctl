#include "CurrentlyPlayingContext.h"

CurrentlyPlayingContext::CurrentlyPlayingContext(nlohmann::json currentlyPlayingJson) {
	device = Device(currentlyPlayingJson["device"]);
	repeatState = currentlyPlayingJson["repeat_state"];
	shuffleState = currentlyPlayingJson["shuffle_state"];
	context = Context(currentlyPlayingJson["context"]);
	timestamp = currentlyPlayingJson["timestamp"];
	progressMs = currentlyPlayingJson["progress_ms"];
	playing = currentlyPlayingJson["playing"];
	track = Track(currentlyPlayingJson["track"]);
}

Device CurrentlyPlayingContext::getDevice() {
	return this->device;
}

std::string CurrentlyPlayingContext::getRepeatState() {
	return this->repeatState;
}

bool CurrentlyPlayingContext::getShuffleState() {
	return this->shuffleState;
}

Context CurrentlyPlayingContext::getContext() {
	return this->context;
}

int CurrentlyPlayingContext::getTimestamp() {
	return this->timestamp;
}

int CurrentlyPlayingContext::getProgressMs() {
	return this->progressMs;
}

bool CurrentlyPlayingContext::isPlaying() {
	return this->playing;
}

Track CurrentlyPlayingContext::getTrack() {
	return this->track;
}

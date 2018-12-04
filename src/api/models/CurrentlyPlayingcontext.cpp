#include "CurrentlyPlayingContext.h"

/**
 * Initializes the context with data received in a JSON
 *
 * @param currentlyPlayingJson JSON containing a user's current player state
 */
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

/**
 *	@return Device that the user is currently playing on
 */
Device CurrentlyPlayingContext::getDevice() {
	return this->device;
}

/**
 * @return Whether the user set repeat to off, track, or context  
 */
std::string CurrentlyPlayingContext::getRepeatState() {
	return this->repeatState;
}


/**
 * @return If shuffle is on or off (true: on), (false: off)
 */
bool CurrentlyPlayingContext::getShuffleState() {
	return this->shuffleState;
}

/**
 * @return the context that the user is playing. Set to NULL if user is using a private session
 */
Context CurrentlyPlayingContext::getContext() {
	return this->context;
}

/**
 * @return Unix Millisecond Timestamp when data was fetched
 */
int CurrentlyPlayingContext::getTimestamp() {
	return this->timestamp;
}

/**
 * @return Progress into the currently playing track. Can be NULL (e.g. If private session is enabled this will be NULL)
 */
int CurrentlyPlayingContext::getProgressMs() {
	return this->progressMs;
}

/**
 * @return Whether or not the user is playing (true: playing) (false: paused)
 */
bool CurrentlyPlayingContext::isPlaying() {
	return this->playing;
}

/**
 * @return The track that the user is currently playing
 */
Track CurrentlyPlayingContext::getTrack() {
	return this->track;
}

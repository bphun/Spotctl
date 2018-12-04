#include "CurrentlyPlayingTrack.h"

/** 
 *
 * Initializes the object with data in the JSON
 * 
 * @param currentlyPlayingJson JSON containing the user's current playing track and its state
 */
CurrentlyPlayingTrack::CurrentlyPlayingTrack(nlohmann::json currentlyPlayingJson) {
    context = Context(currentlyPlayingJson["context"]);
    timestamp = currentlyPlayingJson["timestamp"];
    progressMs = currentlyPlayingJson["progress_ms"];
    playing = currentlyPlayingJson["is_playing"];
    track = Track(currentlyPlayingJson["item"]);
}

/**
 * @return current playing context
 */
Context CurrentlyPlayingTrack::getContext() {
    return this->context;
}

/**
 * @return Unix Millisecond Timestamp when data was fetched
 */
int CurrentlyPlayingTrack::getTimestamp() {
    return this->timestamp;
}

/**
 * @return Progress into the currently playing track. Can be NULL (e.g. If private session is enabled this will be NULL)
 */
int CurrentlyPlayingTrack::getProgressMs() {
    return this->progressMs;
}

/**
 * @return Whether or not the user is playing (true: playing) (false: paused)
 */
bool CurrentlyPlayingTrack::isPlaying() {
    return this->playing;
}

/**
 * @return The track that the user is currently playing
 */
Track CurrentlyPlayingTrack::getTrack() {
    return this->track;
}

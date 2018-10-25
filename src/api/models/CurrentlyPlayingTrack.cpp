#include "CurrentlyPlayingTrack.h"

CurrentlyPlayingTrack::CurrentlyPlayingTrack(nlohmann::json currentlyPlayingJson) {
    context = Context(currentlyPlayingJson["context"]);
    timestamp = currentlyPlayingJson["timestamp"];
    progressMs = currentlyPlayingJson["progress_ms"];
    playing = currentlyPlayingJson["is_playing"];
    track = Track(currentlyPlayingJson["item"]);
}

Context CurrentlyPlayingTrack::getContext() {
    return this->context;
}

int CurrentlyPlayingTrack::getTimestamp() {
    return this->timestamp;
}

int CurrentlyPlayingTrack::getProgressMs() {
    return this->progressMs;
}

bool CurrentlyPlayingTrack::isPlaying() {
    return this->playing;
}

Track CurrentlyPlayingTrack::getTrack() {
    return this->track;
}

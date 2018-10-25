#ifndef CURRENTLY_PLAYING_TRACK_H
#define CURRENTLY_PLAYING_TRACK_H

#include "Track.h"
#include "Context.h"

#include "../utils/json/json.hpp"

class CurrentlyPlayingTrack {

private:

    bool playing;
    int timestamp;
    int progressMs;
    Track track;
    Context context;

public:

    CurrentlyPlayingTrack(nlohmann::json currentlyPlayingJson);

    bool isPlaying();
    int getTimestamp();
    int getProgressMs();
    Track getTrack();
    Context getContext();


};


#endif
#ifndef CURRENTLY_PLAYING_TRACK_H
#define CURRENTLY_PLAYING_TRACK_H

#include "Track.h"
#include "Context.h"

#include "../utils/json.h"

/**
 * Currently Playing Track object
 *
 * The track that the user is currently playing
 *
 */

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
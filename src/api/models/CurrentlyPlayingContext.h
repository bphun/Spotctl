#ifndef CURRENTLY_PLAYING_CONTEXT_H
#define CURRENTLY_PLAYING_CONTEXT_H

#include "Track.h"
#include "Device.h"
#include "Context.h"

#include "../utils/json.h"

/**
 * Current Playing Context
 * 
 * Current state of the user's player i.e if they are currently playing a song, shuffle is enabled, and their current track
 *
 */

class CurrentlyPlayingContext {

private:

    bool playing;
    bool shuffleState;
    int timestamp;
    int progressMs;
    std::string repeatState;
    Track track;
    Device device;
    Context context;

public:

    CurrentlyPlayingContext(nlohmann::json currentlyPlayingJson);

    bool isPlaying();
    bool getShuffleState();
    int getTimestamp();
    int getProgressMs();
    std::string getRepeatState();
    Track getTrack();
    Device getDevice();
    Context getContext();

};


#endif
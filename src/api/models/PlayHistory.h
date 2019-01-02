#ifndef PLAY_HISTORY_OBJECT_H
#define PLAY_HISTORY_OBJECT_H

#include "Track.h"
#include "Context.h"

/**
 * Play history object
 * 
 * Contains a user's play history 
 *
 */

class PlayHistory {

private:

	std::string playedAt;
	Track track;
	Context context;

public:

	PlayHistory(nlohmann::json playHistoryJson);

	std::string getPlayedAt();
	Track getTrack();
	Context getContext();

};

#endif
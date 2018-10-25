#ifndef PLAY_HISTORY_OBJECT_H
#define PLAY_HISTORY_OBJECT_H

#include "Track.h"
#include "Context.h"

#include "../utils/json/json.hpp"

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
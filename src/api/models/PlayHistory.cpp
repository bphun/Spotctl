#include "PlayHistory.h"

/**
 * Initializes the Play history object with the given JSON
 *
 * @param playHistoryJson JSON containing play history data
 */
PlayHistory::PlayHistory(nlohmann::json playHistoryJson) {
	track = Track(playHistoryJson["track"]);
	playedAt = playHistoryJson["played_at"];
	context = Context(playHistoryJson["context"]);
}

/**
 * @return a singular track of the history
 */
Track PlayHistory::getTrack() {
	return this->track;
}

/**
 * @return Date and time the track was played
 */
std::string PlayHistory::getPlayedAt() {
	return this->playedAt;
}

/**
 * @return Context the track was played from
 */
Context PlayHistory::getContext() {
	return this->context;
}

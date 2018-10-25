#include "PlayHistory.h"

PlayHistory::PlayHistory(nlohmann::json playHistoryJson) {
	track = Track(playHistoryJson["track"]);
	playedAt = playHistoryJson["played_at"];
	context = Context(playHistoryJson["context"]);
}

Track PlayHistory::getTrack() {
	return this->track;
}

std::string PlayHistory::getPlayedAt() {
	return this->playedAt;
}

Context PlayHistory::getContext() {
	return this->context;
}

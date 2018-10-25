#include "RecommendationsSeed.h"

RecommendationsSeed::RecommendationsSeed(nlohmann::json reccomendationsJson) {
    afterFilteringSize = reccomendationsJson["afterFilteringSize"];
    afterRelinkingSize = reccomendationsJson["afterRelinkingSize"];
    href = reccomendationsJson["href"];
    id = reccomendationsJson["id"];
    initialPoolSize = reccomendationsJson["initialPoolSize"];
    type = reccomendationsJson["type"];
}

int RecommendationsSeed::getAfterFilteringSize() {
    return this->afterFilteringSize;
}

int RecommendationsSeed::getAfterRelinkingSize() {
    return this->afterRelinkingSize;
}

std::string RecommendationsSeed::getHref() {
    return this->href;
}

std::string RecommendationsSeed::getId() {
    return this->id;
}

int RecommendationsSeed::getInitialPoolSize() {
    return this->initialPoolSize;
}

std::string RecommendationsSeed::getType() {
    return this->type;
}
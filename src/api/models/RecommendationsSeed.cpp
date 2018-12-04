#include "RecommendationsSeed.h"

/**
 * Initializes the reccommendations seed with data in the given JSON
 *
 * @param recomendationsSeedJson JSON containing seed data
 */
RecommendationsSeed::RecommendationsSeed(nlohmann::json recomendationsSeedJson) {
    afterFilteringSize = recomendationsSeedJson["afterFilteringSize"];
    afterRelinkingSize = recomendationsSeedJson["afterRelinkingSize"];
    href = recomendationsSeedJson["href"];
    id = recomendationsSeedJson["id"];
    initialPoolSize = recomendationsSeedJson["initialPoolSize"];
    type = recomendationsSeedJson["type"];
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

std::string RecommendationsSeed::getid() {
    return this->id;
}

int RecommendationsSeed::getInitialPoolSize() {
    return this->initialPoolSize;
}

std::string RecommendationsSeed::getType() {
    return this->type;
}
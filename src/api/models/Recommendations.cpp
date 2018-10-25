#include "Recommendations.h"

Recommendations::Recommendations(nlohmann::json recomendationsJson) {
    for (nlohmann::json json : recomendationsJson["seeds"]) {
        seeds.push_back(RecommendationsSeed(json));
    }

    for(nlohmann::json json : recomendationsJson["tracks"]) {
        tracks.push_back(Track(json));
    }
}

std::vector<RecommendationsSeed> Recommendations::getSeeds() {
    return this->seeds;
}

std::vector<Track> Recommendations::getTracks() {
    return this->tracks;
}
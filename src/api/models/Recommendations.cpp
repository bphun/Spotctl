#include "Recommendations.h"

/**
 * Initializes the user's recommendations with data in the given JSON
 *
 * @param recommendationsJson JSON containing a user's recommended tracks
 */
Recommendations::Recommendations(nlohmann::json recomendationsJson) {
    for (nlohmann::json json : recomendationsJson["seeds"]) {
        seeds.push_back(RecommendationsSeed(json));
    }

    for(nlohmann::json json : recomendationsJson["tracks"]) {
        tracks.push_back(Track(json));
    }
}

/**
 * @return Vector of recommendation seeds
 */
std::vector<RecommendationsSeed> Recommendations::getSeeds() {
    return this->seeds;
}

/**
 * @return Vector of the user's recommended tracks
 */
std::vector<Track> Recommendations::getTracks() {
    return this->tracks;
}
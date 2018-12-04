#ifndef RECCOMENDATIONS_H
#define RECCOMENDATIONS_H

#include <vector>

#include "Track.h"
#include "RecommendationsSeed.h"

#include "../utils/json.h"

/**
 * Recommendation Object
 *
 * Stores a user's recommended tracks
 *
 */

class Recommendations {

private:
	
	std::vector<Track> tracks;
	std::vector<RecommendationsSeed> seeds;

public:

	Recommendations(nlohmann::json recomendationsJson);

	std::vector<Track> getTracks();
	std::vector<RecommendationsSeed> getSeeds();

};


#endif
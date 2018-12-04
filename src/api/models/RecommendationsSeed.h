#ifndef RECOMMENDATIONS_SEED_H
#define RECOMMENDATIONS_SEED_H

#include <string>

#include "../utils/json.h"

/**
 * Recommendation Seed Object
 * 
 * Object containing 
 *
 */

class RecommendationsSeed {

private:

    int initialPoolSize;
    int afterFilteringSize;
    int afterRelinkingSize;
    std::string id;
    std::string href;
    std::string type;

public:

    RecommendationsSeed(nlohmann::json recomendationsJson);

    int getInitialPoolSize();
    int getAfterFilteringSize();
    int getAfterRelinkingSize();
    std::string getid();
    std::string getHref();
    std::string getType();

};

#endif
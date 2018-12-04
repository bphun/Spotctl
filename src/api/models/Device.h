#ifndef DEVICE_H
#define DEVICE_H

#include <string>

#include "../utils/json.h"

/**
 * Device object
 *
 * Contains data associated with devices linked with a user's spotify account
 *
 */

class Device {

private:

    bool active;
    bool restricted;
    int volumePercent;
    std::string id;
    std::string name;
    std::string type;

public:

    Device();
    Device(nlohmann::json deviceJson);

    bool isActive();
    bool isRestricted();
    int getVolumePercent();
    std::string getid();
    std::string getName();
    std::string getType();
    
};

#endif
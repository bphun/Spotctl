#include "Device.h"

Device::Device() = default;

/**
 * Initializes the device object with the given JSON
 * 
 * @param deviceJson JSON containing device data
 */
Device::Device(nlohmann::json deviceJson) {
	id = deviceJson["id"];
	active = deviceJson["is_active"];
	restricted = deviceJson["is_restricted"];
	name = deviceJson["name"];
	type = deviceJson["type"];
	volumePercent = deviceJson["volume_percent"];
}

/**
 * @return The device's Spotify ID
 */
std::string Device::getid() {
	return this->id;
}

/**
 * @return Whether or not the device is active (true: active) (false: inactive)
 */
bool Device::isActive() {
	return this->active;
}

/**
 * @return Whether controlling this device is restricted. If “true” then no Web API commands will be accepted by this device.
 */
bool Device::isRestricted() {
	return this->restricted;
}

/**
 * @return The device's name
 */
std::string Device::getName() {
	return this->name;
}

/**
 * @return The Device's type (Computer, Smartphone, Speaker)
 */
std::string Device::getType() {
	return this->type;
}

/**
 * @return The current volume in percent. This may be null.
 */
int Device::getVolumePercent() {
	return this->volumePercent;
}

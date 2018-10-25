#include "Device.h"

Device::Device() = default;

Device::Device(nlohmann::json deviceJson) {
	id = deviceJson["id"];
	active = deviceJson["is_active"];
	restricted = deviceJson["is_restricted"];
	name = deviceJson["name"];
	type = deviceJson["type"];
	volumePercent = deviceJson["volume_percent"];
}

std::string Device::getId() {
	return this->id;
}

bool Device::isActive() {
	return this->active;
}

bool Device::isRestricted() {
	return this->restricted;
}

std::string Device::getName() {
	return this->name;
}

std::string Device::getType() {
	return this->type;
}

int Device::getVolumePercent() {
	return this->volumePercent;
}

#include "yaml-cpp/yaml.h"
#include "configuration.h"

Configuration::Configuration(const std::string& config_filepath) {
    YAML::Node config_object = YAML::LoadFile(config_filepath);
    this->port = config_object["port"].as<std::string>();
    this->player_health = config_object["game_settings"]["player_health"].as<int>();
    // this->weapons = config_object["game_settings"].as<>()["weapons"].as<WeaponConfig>();
}

const std::string& Configuration::getPort() const {
    return this->port;
}

int Configuration::getWeaponConfigValue(const std::string& weapon_name, const std::string& key) const {
    return this->weapons.at(weapon_name).at(key);
}

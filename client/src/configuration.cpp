#include "yaml-cpp/yaml.h"
#include "configuration.h"

#define WEAPON_TYPES {"knife", "glock"}
#define WEAPON_PARAMS {"damage", "precision", "range"}

Configuration::Configuration(const std::string& config_filepath) {
    YAML::Node config = YAML::LoadFile(config_filepath);
    this->port = config["port"].as<std::string>();

    YAML::Node game = config["game_settings"];
    this->player_health = game["player_health"].as<float>();

    YAML::Node weapons = game["weapons"];
    std::vector<std::string> weapon_types = WEAPON_TYPES;
    std::vector<std::string> weapon_params = WEAPON_PARAMS;

    for (const std::string& weapon_type : weapon_types) {
        this->weapons[weapon_type] = std::unordered_map<std::string, float>();

        for (const std::string& weapon_params : weapon_params) {
            this->weapons[weapon_type] = weapons[weapon_type][weapon_params];
        }
    }
}

const std::string& Configuration::getPort() const {
    return this->port;
}

float Configuration::getWeaponConfigValue(const std::string& weapon_name, const std::string& key) const {
    return this->weapons.at(weapon_name).at(key);
}

float Configuration::getPlayerHealth() const {
    return this->player_health;
}

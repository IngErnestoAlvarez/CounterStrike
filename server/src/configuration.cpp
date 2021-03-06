#include "configuration.h"

#include "yaml-cpp/yaml.h"

#define WEAPON_TYPES \
    { "knife", "glock", "ak47", "m3", "awp" }
#define WEAPON_PARAMS \
    { "damage", "precision", "range", "initial_ammo", "price" }

Configuration::Configuration(const std::string &config_filepath) {
    YAML::Node config = YAML::LoadFile(config_filepath);
    this->port = config["port"].as<std::string>();

    YAML::Node game = config["game_settings"];
    this->player_health = game["player_health"].as<int>();
    this->player_speed = game["player_speed"].as<float>();
    this->bullet_speed = game["bullet_speed"].as<float>();
    this->initial_money = game["initial_money"].as<int>();
    this->initial_ammo = game["initial_ammo"].as<int>();
    this->kill_reward = game["kill_reward"].as<int>();
    this->map_filepath = game["map_filepath"].as<std::string>();

    YAML::Node weapons = game["weapons"];
    std::vector<std::string> weapon_types = WEAPON_TYPES;
    std::vector<std::string> weapon_params = WEAPON_PARAMS;

    for (const std::string &weapon_type : weapon_types) {
        this->weapons[weapon_type] = std::unordered_map<std::string, float>();

        for (const std::string &weapon_param : weapon_params) {
            this->weapons[weapon_type][weapon_param] =
                weapons[weapon_type][weapon_param].as<float>();
        }
    }
}

const std::string &Configuration::getPort() const { return this->port; }

float Configuration::getWeaponConfigValue(const std::string &weapon_name,
                                          const std::string &key) const {
    return this->weapons.at(weapon_name).at(key);
}

int Configuration::getPlayerHealth() const { return this->player_health; }

float Configuration::getPlayerSpeed() const { return this->player_speed; }

float Configuration::getBulletSpeed() const { return this->bullet_speed; }

int Configuration::getInitialMoney() const { return this->initial_money; }

int Configuration::getInitialAmmo() const { return this->initial_ammo; }

int Configuration::getKillReward() const { return this->kill_reward; }

std::string Configuration::getMapFilepath() const {
    return this->map_filepath;
}

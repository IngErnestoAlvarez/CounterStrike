#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <unordered_map>
#include <string>

class Configuration {
private:
    std::string port;
    float player_health;
    float player_speed;
    float bullet_speed;
    int initial_money;
    int kill_reward;
    std::unordered_map<std::string,
    				   std::unordered_map<std::string, float>> weapons;

public:
    Configuration(const std::string& config_filepath);
    const std::string& getPort() const;
    float getWeaponConfigValue(const std::string& weapon_name, const std::string& key) const;
    int getPlayerHealth() const;
    float getPlayerSpeed() const;
    float getBulletSpeed() const;
    int getInitialMoney() const;
    int getKillReward() const;
};

#endif

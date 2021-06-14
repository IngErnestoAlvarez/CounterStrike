#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Configuration;

class Weapon {
private:
    std::string name;
    float precision;
    float damage;
    float range;

public:
    Weapon(const std::string& name,
           const Configuration& config);
    virtual void use() = 0;
    ~Weapon();
};

#endif

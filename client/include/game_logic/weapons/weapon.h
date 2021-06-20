#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon {
private:
    std::string name;
    float damage;
    float precision;
    float range;

public:
    Weapon(const std::string& name,
           float damage,
           float precision,
           float range);
    virtual void use() = 0;
    ~Weapon();
};

#endif

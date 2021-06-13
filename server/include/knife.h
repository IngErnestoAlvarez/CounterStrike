#ifndef KNIFE_H
#define KNIFE_H

#include "../include/weapon.h"
class Configuration;

class Knife: public Weapon {
public:
    Knife(const Configuration& config);
    void use() override;
};

#endif

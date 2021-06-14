#ifndef GLOCK_H
#define GLOCK_H

#include "../include/weapon.h"
class Configuration;

class Glock: public Weapon {
public:
    Glock(const Configuration& config);
    void use() override;
};

#endif

#ifndef KNIFE_H
#define KNIFE_H

#include "weapon.h"

class Knife : public Weapon {
public:
    Knife(float damage, float precision, float range);
    void use() override;
};

#endif

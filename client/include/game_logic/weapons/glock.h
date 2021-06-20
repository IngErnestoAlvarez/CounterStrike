#ifndef GLOCK_H
#define GLOCK_H

#include "weapon.h"

class Glock : public Weapon {
public:
    Glock(float damage, float precision, float range);
    void use() override;
};

#endif

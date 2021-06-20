#include "game_logic/weapons/glock.h"

#include "configuration.h"

Glock::Glock(float damage, float precision, float range)
          : Weapon("Glock", damage, precision, range) {}

void Glock::use() {}

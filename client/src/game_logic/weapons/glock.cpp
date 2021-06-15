#include "game_logic/weapons/glock.h"

#include "configuration.h"

Glock::Glock(const Configuration &config) : Weapon("Glock", config) {}

void Glock::use() {}

#include "game_logic/weapons/knife.h"

#include "configuration.h"

Knife::Knife(float damage, float precision, float range)
           : Weapon("Knife", damage, precision, range) {}

void Knife::use() {}

#include "game_logic/weapons/knife.h"

#include "configuration.h"

Knife::Knife(const Configuration &config) : Weapon("Knife", config) {}

void Knife::use() {}

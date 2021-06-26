#include "game_logic/weapons/knife.h"

Knife::Knife(Game& game, Body& player)
           : Weapon("knife", game, player) {}

void Knife::use() {}

#include "game_logic/weapons/knife.h"
#include "types.h"

Knife::Knife(Game& game, Player& player)
           : Weapon("knife", KNIFE_TYPE, game, player) {}

void Knife::use() {}

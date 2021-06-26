#include "game_logic/weapons/weapon_factory.h"
#include "game_logic/game.h"
#include "game_logic/player.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapons/knife.h"
#include "game_logic/weapons/glock.h"
#include "game_logic/weapons/ak47.h"
#include "game_logic/weapons/m3.h"
#include "game_logic/weapons/awp.h"

Weapon* WeaponFactory::create(Game& game,
                              Player& player,
                              const std::string& weapon_name) {
    if (weapon_name == "knife")
        return new Knife(game, player);

    if (weapon_name == "glock")
        return new Glock(game, player);

    if (weapon_name == "ak47")
        return new AK47(game, player);

    if (weapon_name == "m3")
        return new M3(game, player);

    if (weapon_name == "awp")
        return new AWP(game, player);

    // terminar esto

    return nullptr;
}

#ifndef __PLAYER_VIEW_H__
#define __PLAYER_VIEW_H__

#include <memory>
#include <string>
#include <vector>

#include "game_io/ammo_view.h"
#include "game_io/life_view.h"
#include "game_io/sdl/SdlObject.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlText.h"
#include "game_io/sound/sample.h"
#include "game_io/stencil.h"
#include "game_io/weapon.h"
#include "game_logic/player.h"

class PlayerView : public SdlObject {
   private:
    Player *player;
    size_t animation_pos;
    Stencil stencil;
    WeaponView primaryWeapon;
    lifeView life;
    AmmoView ammo;

   public:
    PlayerView(std::string const &path, int animation_frames,
               SdlWindow &window);
    PlayerView(std::string const &path, int animation_frames, SdlWindow &window,
               Player *player);

    ~PlayerView();

    void mouse_mov(int x, int y) override;
    void render() override;

    void shootWeapon();

    float get_angle();

   private:
    void update_animation();

    void selectAnimationPositions();
};

#endif

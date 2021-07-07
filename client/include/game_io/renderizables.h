#ifndef __RENDERIZABLES_H__
#define __RENDERIZABLES_H__

#include <memory>
#include <vector>

#include "game_io/floor.h"
#include "game_io/player.h"
#include "game_io/sdl/SdlObject.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlText.h"
#include "game_proxy/body_proxy.h"
#include "game_proxy/player_proxy.h"

class Renderizables {
   private:
    SdlWindow *window;
    std::vector<std::unique_ptr<SdlObject>> objects;
    std::unique_ptr<PlayerView> player;
    Floor floor;

   public:
    Renderizables(SdlWindow &window, PlayerProxy *player);

    ~Renderizables();

    void render();

    void shootWeapon();

    void renderObjects(bodyVector::iterator it, bodyVector::iterator end);
    void renderFloor(bodyVector::iterator it, bodyVector::iterator end);
    void renderPlayer();

    void createStatics(bodyVector::iterator it, bodyVector::iterator end);

    void modifyTexturesIfDead();

   private:
    void createPlayer(PlayerProxy *player);

    void createObject(BodyType type);

    void camFilter(Uint8 r, Uint8 g, Uint8 b);
};

#endif

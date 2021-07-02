#ifndef __RENDERIZABLES_H__
#define __RENDERIZABLES_H__

#include <memory>
#include <vector>

#include "game_io/player.h"
#include "game_io/sdl/SdlObject.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlText.h"
#include "game_logic/body.h"
#include "game_logic/map.h"
#include "game_logic/player.h"

class Renderizables {
   private:
    std::vector<std::unique_ptr<SdlText>> texts;
    std::vector<std::unique_ptr<SdlObject>> objects;
    std::unique_ptr<PlayerView> player;
    SdlWindow *window;
    Map *map;

   public:
    // Renderizables(SdlWindow &window);
    Renderizables(SdlWindow &window, std::vector<Body *> bodies, Player *player,
                  Map *map);

    ~Renderizables();

    void render();

    void mouseMove(int posX, int posY);

    void shootWeapon();

   private:
    void renderTexts();

    void renderObjects();

    void renderFloor();

    void createTexts();

    void createFloor();

    void createObjects();
    void createObjects(std::vector<Body *> bodies);
    void createObjects(std::vector<Body *> bodies, Player *player);
};

#endif

#ifndef __RENDERIZABLES_H__
#define __RENDERIZABLES_H__

#include <memory>
#include <vector>

#include "game_io/sdl/SdlObject.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlText.h"

class Renderizables {
   private:
    std::vector<std::unique_ptr<SdlText>> texts;
    std::vector<std::unique_ptr<SdlObject>> objects;
    SdlWindow *window;

   public:
    Renderizables(SdlWindow &window);

    ~Renderizables();

    void render();

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void mouseMove(int posX, int posY);

   private:
    void renderTexts();

    void renderObjects();

    void createTexts();

    void createObjects();
};

#endif

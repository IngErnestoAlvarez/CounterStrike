#ifndef __RENDERIZABLES_H__
#define __RENDERIZABLES_H__

#include <vector>

#include "game_io/sdl/SdlObject.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlText.h"

class Renderizables {
   private:
    std::vector<SdlImage> images;
    std::vector<SdlText> texts;
    std::vector<SdlObject> objects;
    SdlWindow *window;

   public:
    Renderizables(SdlWindow &window);

    ~Renderizables();

    void render();

   private:
    void renderImages();

    void renderTexts();

    void renderObjects();

    void createImages();

    void createTexts();

    void createObjects();
};

#endif

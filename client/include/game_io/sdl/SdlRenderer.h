#ifndef __SDLRENDERER_H__
#define __SDLRENDERER_H__

#include <SDL2/SDL.h>

#include "SdlWindow.h"

class SdlRenderer {
   private:
    SDL_Renderer *renderer;

   public:
    SdlRenderer(SdlWindow &window);
};

#endif

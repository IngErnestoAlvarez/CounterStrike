#ifndef __SDLTEXTURE_H__
#define __SDLTEXTURE_H__

#include <SDL2/SDL.h>

#include "game_io/sdl/SdlWindow.h"

class SdlTexture {
   private:
    SDL_Texture *texture;

   public:
    SdlTexture();
    SdlTexture(int width, int height, SdlWindow &renderer);

    SdlTexture &operator=(SDL_Texture *);

    ~SdlTexture();

   private:
    void empty();
};

#endif

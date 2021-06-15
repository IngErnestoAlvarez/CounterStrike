#ifndef __SDLSURFACE_H__
#define __SDLSURFACE_H__

#include <SDL2/SDL.h>

#include "game_io/sdl/SdlTexture.h"

class SdlSurface {
   private:
    SDL_Surface *surface;

   public:
    SdlSurface(int width, int height);

    SdlTexture transform_to_texture();

   private:
    void set_rgba_mask(Uint32 &rmask, Uint32 &gmask, Uint32 &bmask,
                       Uint32 &amask);
};

#endif

#ifndef __SDLSURFACE_H__
#define __SDLSURFACE_H__

#include <SDL2/SDL.h>

#include <string>

#include "game_io/sdl/SdlTexture.h"
#include "game_io/sdl/text/SdlFont.h"

class SdlText;

class SdlSurface {
   private:
    SDL_Surface *surface;

   public:
    SdlSurface();
    SdlSurface(int width, int height);
    SdlSurface(SDL_Surface *surface);

    SdlSurface &operator=(SDL_Surface *surface);

    ~SdlSurface();

    SdlTexture transform_to_texture(SdlWindow &window);

   private:
    void set_rgba_mask(Uint32 &rmask, Uint32 &gmask, Uint32 &bmask,
                       Uint32 &amask);

    void empty();
};

#endif

#ifndef __SDLTEXTURE_H__
#define __SDLTEXTURE_H__

#include <SDL2/SDL.h>

class SdlTexture {
   private:
    SDL_Texture *texture;

   public:
    SdlTexture(int width, int height, SdlRenderer renderer);
};

#endif

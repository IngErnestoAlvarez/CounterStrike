#ifndef __SDLTEXTURE_H__
#define __SDLTEXTURE_H__

#include <SDL2/SDL.h>

#include "game_io/sdl/SdlWindow.h"

class SdlTexture {
   protected:
    SDL_Texture *texture;
    SdlWindow *window;
    int width;
    int height;

   public:
    SdlTexture(SdlWindow &window);
    SdlTexture(int width, int height, SdlWindow &renderer);
    SdlTexture(SdlTexture const &) = delete;
    SdlTexture(SdlTexture &&);

    SdlTexture &operator=(SdlTexture const &) = delete;
    SdlTexture &operator=(SdlTexture &&);
    SdlTexture &operator=(SDL_Texture *);

    void render(SdlWindow &renderer, int x, int y, float angle,
                SDL_Point &center, SDL_Rect *clip = nullptr);

    void render(SdlWindow &renderer, SDL_Rect &rect);

    virtual ~SdlTexture();

   protected:
    void empty();
};

#endif
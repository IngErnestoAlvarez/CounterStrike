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

    void render(int x, int y, float angle, SDL_Point &center,
                SDL_Rect *clip = nullptr, SDL_Rect *renderQuad = nullptr);

    void render(SDL_Point &pos);

    void renderAbsolute(int x, int y, float angle, SDL_Point &center,
                        SDL_Rect *clip = nullptr,
                        SDL_Rect *renderQuad = nullptr);

    /**
     * @brief Usar antes del render
     *
     */
    void set_alpha(Uint8 alpha);

    /**
     * @brief Hacerlo despues de crear la textura
     *
     */
    void set_blendMode(SDL_BlendMode mode);

    virtual ~SdlTexture();

    void setColorMod(Uint8 r, Uint8 g, Uint8 b);

   protected:
    void empty();
};

#endif

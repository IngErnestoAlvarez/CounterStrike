#include "sdl/copy_to_png.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <vector>

Cpy2Png::Cpy2Png(std::string const &dir) : dir(dir), filename("stencil.png") {}

Cpy2Png::Cpy2Png() : Cpy2Png("/") {}

void Cpy2Png::copy_to_png(SDL_Renderer *renderer, int width, int height) {
    Uint32 rmask, gmask, bmask, amask;
    this->check_masks(rmask, gmask, bmask, amask);

    std::vector<uint8_t> pixels(width * height, 0);
    SDL_RenderReadPixels(renderer, NULL, 0, pixels.data(), 2);

    SDL_Surface *surf =
        SDL_CreateRGBSurfaceFrom(pixels.data(), width, height, 32, 4 * width,
                                 rmask, gmask, bmask, amask);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surf);
    this->save_texture(renderer, text);
    SDL_DestroyTexture(text);
    SDL_FreeSurface(surf);
}

void Cpy2Png::save_texture(SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_Texture *target = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, texture);
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_Surface *surface =
        SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(renderer, NULL, surface->format->format,
                         surface->pixels, surface->pitch);
    IMG_SavePNG(surface, (this->dir + this->filename).c_str());
    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(renderer, target);
}

void Cpy2Png::check_masks(Uint32 &rmask, Uint32 &gmask, Uint32 &bmask,
                          Uint32 &amask) {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
}

#include "game_io/sdl/SdlSurface.h"

#include <SDL2/SDL.h>

#include <stdexcept>
#include <utility>

SdlSurface::SdlSurface() { this->surface = nullptr; }

SdlSurface::SdlSurface(int width, int height) {
    Uint32 r, g, b, a;
    this->set_rgba_mask(r, g, b, a);
    this->surface = SDL_CreateRGBSurface(0, width, height, 32, r, g, b, a);
}

SdlSurface &SdlSurface::operator=(SDL_Surface *surface) {
    this->empty();
    this->surface = surface;
    return *this;
}

SdlSurface::~SdlSurface() { this->empty(); }

void SdlSurface::empty() {
    if (this->surface != nullptr) {
        SDL_FreeSurface(this->surface);
        this->surface = nullptr;
    }
}

SdlTexture SdlSurface::transform_to_texture(SdlWindow &window) {
    SdlTexture aux(window);
    SDL_Texture *auxsurf =
        SDL_CreateTextureFromSurface(window.getRendered(), this->surface);
    if (auxsurf == NULL) throw std::runtime_error("Error transform2texture");
    aux = auxsurf;
    return aux;
}

void SdlSurface::set_rgba_mask(Uint32 &rmask, Uint32 &gmask, Uint32 &bmask,
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

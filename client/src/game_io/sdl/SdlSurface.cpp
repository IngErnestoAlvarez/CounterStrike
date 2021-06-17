#include "game_io/sdl/SdlSurface.h"

#include <SDL2/SDL.h>

#include "game_io/sdl/text/SdlFont.h"

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

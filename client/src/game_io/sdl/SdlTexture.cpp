#include "game_io/sdl/SdlTexture.h"

#include <SDL2/SDL.h>

SdlTexture::SdlTexture() : texture(nullptr) {}

SdlTexture::SdlTexture(int width, int height, SdlWindow &renderer) {
    this->texture =
        SDL_CreateTexture(renderer.getRendered(), SDL_PIXELFORMAT_ABGR8888,
                          SDL_TEXTUREACCESS_TARGET, width, height);
}

SdlTexture::~SdlTexture() { this->empty(); }

SdlTexture &SdlTexture::operator=(SDL_Texture *texture) {
    this->empty();
    this->texture = texture;

    return *this;
}

void SdlTexture::empty() {
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}

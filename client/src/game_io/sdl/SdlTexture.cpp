#include "game_io/sdl/SdlTexture.h"

#include <SDL2/SDL.h>

#include <stdexcept>

#include "game_io/sdl/SdlWindow.h"

SdlTexture::SdlTexture(SdlWindow &window)
    : texture(nullptr), window(&window), width(0), height(0) {}

SdlTexture::SdlTexture(int width, int height, SdlWindow &window)
    : window(&window), width(width), height(height) {
    this->texture =
        SDL_CreateTexture(window.getRendered(), SDL_PIXELFORMAT_ABGR8888,
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

void SdlTexture::render(SdlWindow &renderer, int x, int y, float angle,
                        SDL_Point &center, SDL_Rect *clip) {
    if (this->texture == nullptr) throw std::logic_error("No hay textura");
    SDL_Rect renderQuad = {x, y, this->width, this->height};
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer.getRendered(), this->texture, clip, &renderQuad,
                     angle, &center, flip);
}

#include "game_io/sdl/SdlTexture.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <stdexcept>

#include "game_io/sdl/SdlWindow.h"

SdlTexture::SdlTexture(SdlWindow &window)
    : texture(nullptr), window(&window), width(0), height(0) {}

SdlTexture::SdlTexture(int width, int height, SdlWindow &window)
    : window(&window), width(width), height(height) {
    this->texture =
        SDL_CreateTexture(window.getRendered(), SDL_PIXELFORMAT_ABGR8888,
                          SDL_TEXTUREACCESS_TARGET, width, height);
    if (this->texture == nullptr)
        throw std::runtime_error("Error al crear textura");
}

SdlTexture::~SdlTexture() { this->empty(); }

SdlTexture &SdlTexture::operator=(SDL_Texture *texture) {
    this->empty();
    this->texture = texture;
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    this->width = w;
    this->height = h;

    return *this;
}
SdlTexture::SdlTexture(SdlTexture &&other)
    : texture(other.texture),
      window(other.window),
      width(other.width),
      height(other.height) {
    other.texture = nullptr;
    other.window = nullptr;
    other.width = 0;
    other.height = 0;
}

SdlTexture &SdlTexture::operator=(SdlTexture &&other) {
    if (this == &other) return *this;
    this->texture = other.texture;
    other.texture = nullptr;
    this->width = other.width;
    other.width = 0;
    this->height = other.height;
    other.height = 0;
    this->window = other.window;
    other.window = nullptr;

    return *this;
}

void SdlTexture::empty() {
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}

void SdlTexture::render(int x, int y, float angle, SDL_Point &center,
                        SDL_Rect *clip, SDL_Rect *renderQuad) {
    SDL_Rect rectaux;
    if (this->texture == nullptr) throw std::logic_error("No hay textura");
    if (renderQuad == nullptr) {
        renderQuad = &rectaux;
        if (clip != nullptr) {
            renderQuad->w = clip->w;
            renderQuad->h = clip->h;
        }
    }

    renderQuad->x = x - window->getCamera().x;
    renderQuad->y = y - window->getCamera().y;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (SDL_RenderCopyEx(window->getRendered(), this->texture, clip, renderQuad,
                         angle, &center, flip)) {
        throw std::runtime_error("Error RenderCopyEx");
    }
}

void SdlTexture::render(SDL_Point &pos) {
    if (this->texture == nullptr) throw std::logic_error("No hay textura");
    SDL_Rect rect;

    rect.w = this->width;
    rect.h = this->height;
    rect.x = pos.x;
    rect.y = pos.y;

    if (SDL_RenderCopy(window->getRendered(), this->texture, NULL, &rect)) {
        std::cout << SDL_GetError() << std::endl;
        throw std::runtime_error("Error RenderCopy");
    }
}

void SdlTexture::set_blendMode(SDL_BlendMode mode) {
    SDL_SetTextureBlendMode(this->texture, mode);
}

void SdlTexture::set_alpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(this->texture, alpha);
}

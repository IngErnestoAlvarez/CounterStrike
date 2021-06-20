#include "game_io/sdl/SdlWindow.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <stdexcept>
#include <vector>

SdlWindow::SdlWindow()
    : window(nullptr), renderer(nullptr), width(0), height(0) {}

SdlWindow::SdlWindow(int width, int height) : width(width), height(height) {
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
        throw std::runtime_error("Window could not be created!");
    }

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
        throw std::runtime_error("Renderer could not be created!");
    }
}

SdlWindow::~SdlWindow() {
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }
    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
}
SdlWindow &SdlWindow::operator=(SdlWindow &&other) {
    if (this == &other) return *this;

    this->window = other.window;
    other.window = nullptr;
    this->renderer = other.renderer;
    other.window = nullptr;
    this->width = other.width;
    other.width = 0;
    this->height = other.height;
    other.height = 0;
    return *this;
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() { this->fill(0x33, 0x33, 0x33, 0xFF); }

void SdlWindow::render() { SDL_RenderPresent(this->renderer); }

SDL_Renderer *SdlWindow::getRendered() const {
    if (this->renderer == NULL) throw;
    return this->renderer;
}

void SdlWindow::clear_renderer() { SDL_RenderClear(this->renderer); }

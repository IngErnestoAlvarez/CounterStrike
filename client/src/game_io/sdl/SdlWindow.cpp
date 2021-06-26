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
    this->camera.x = 0;
    this->camera.y = 0;
    this->camera.w = 300;
    this->camera.h = 200;
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

SDL_Rect &SdlWindow::getCamera() { return this->camera; }

void SdlWindow::clear_renderer() { SDL_RenderClear(this->renderer); }

void SdlWindow::set_camera_pos(int x, int y, int widthtotal, int heighttotal) {
    this->camera.x = (x + 32 / 2) - width / 2;
    this->camera.y = (y + 32 / 2) - height / 2;

    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > widthtotal - camera.w) {
        camera.x = widthtotal - camera.w;
    }
    if (camera.y > heighttotal - camera.h) {
        camera.y = heighttotal - camera.h;
    }
}

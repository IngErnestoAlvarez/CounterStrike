#include "SdlWindow.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

SdlWindow::SdlWindow(int width, int height) : width(width), height(height) {
    int code = SDL_Init(SDL_INIT_VIDEO);
    if (code) {
        // SDl exception
    }
    code = SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
                                       &this->window, &this->renderer);
    if (code) {
        // SDL exception
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

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() { this->fill(0x33, 0x33, 0x33, 0xFF); }

void SdlWindow::render() { SDL_RenderPresent(this->renderer); }

SDL_Renderer *SdlWindow::getRendered() const { return this->renderer; }

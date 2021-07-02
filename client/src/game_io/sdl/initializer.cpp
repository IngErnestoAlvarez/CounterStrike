#include "game_io/sdl/initializer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <syslog.h>

#include <stdexcept>

Initializer::Initializer() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw std::runtime_error("SDL could not initialize!");
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        syslog(LOG_WARNING, "Linear texture filtering not enabled!");
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_Quit();
        throw std::runtime_error("SDL_image could not initialize!");
    }

    if (TTF_Init() < 0) {
        SDL_Quit();
        throw std::runtime_error("SDL_ttf could not initialize!");
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        SDL_Quit();
        throw std::runtime_error("SDL_Mixer could not initialize!");
    }
}

Initializer::~Initializer() {
    IMG_Quit();
    SDL_Quit();
    Mix_CloseAudio();
}

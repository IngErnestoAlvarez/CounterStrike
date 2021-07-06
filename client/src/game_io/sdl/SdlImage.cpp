#include "game_io/sdl/SdlImage.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "game_io/sdl/SdlWindow.h"

SdlImage::SdlImage(SdlWindow &window) : SdlTexture(window) {}

SdlImage::SdlImage(SdlWindow &window, std::string const &path)
    : SdlTexture(window) {
    this->load_from_file(path);
}
SdlImage::SdlImage(SdlWindow &window, BodyType type) : SdlTexture(window) {
    this->load_from_file(getBodyPath(type));
}

SdlImage::SdlImage(SdlImage &&other) : SdlTexture(std::move(other)) {
    width = other.width;
    other.width = 0;
    height = other.height;
    other.height = 0;
}

SdlImage &SdlImage::operator=(SdlImage &&other) {
    if (this == &other) return *this;
    SdlTexture::operator=(std::move(other));
    width = other.width;
    other.width = 0;
    height = other.height;
    other.height = 0;
    return *this;
}

SdlImage::~SdlImage() { this->empty(); }

void SdlImage::load_from_file(std::string const &path) {
    load_from_file(path, 0xFF, 0xFF, 0xFF);
}

void SdlImage::load_from_file(std::string const &path, Uint8 red, Uint8 green,
                              Uint8 blue) {
    this->empty();
    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        throw std::runtime_error("Unable to load image ! SDL_image Error:");
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE,
                        SDL_MapRGB(loadedSurface->format, red, green, blue));

        newTexture = SDL_CreateTextureFromSurface(this->window->getRendered(),
                                                  loadedSurface);
        if (newTexture == NULL) {
            throw std::runtime_error("Unable to create texture! ");
        } else {
            this->width = loadedSurface->w;
            this->height = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }

    this->texture = newTexture;
    if (this->texture == NULL)
        throw std::runtime_error("Problemas con la carga de la textura");
}

std::string SdlImage::getBodyPath(BodyType type) {
    switch (type) {
        case NO_BODY_TYPE:
            break;
        case CT1_TYPE:
            break;
        case CT2_TYPE:
            return std::string("assets/sprites/ct2.png");
            break;
        case AK47_TYPE:
            return std::string("assets/sprites/ak47.png");
            break;
        case AK47_D_TYPE:
            return std::string("assets/sprites/ak47_d.png");
            break;
        case OFFICE_TYPE:
            return std::string("assets/sprites/office.png");
            break;
        case PLAYER_TYPE:
            return std::string("assets/sprites/player.png");
            break;
        case WALL_TYPE:
            return std::string("assets/sprites/wall.png");
            break;
    }
    throw std::logic_error("BodyType erroneo");
    return std::string("");
}

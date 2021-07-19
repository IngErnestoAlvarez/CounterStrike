#include "game_io/sdl/SdlImage.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "game_io/sdl/SdlWindow.h"

const SDL_Color WHITE = {0xFF, 0xFF, 0xFF};
const SDL_Color BLACK = {0x00, 0x00, 0x00};
const SDL_Color PINK = {0xff, 0x00, 0xff};

#ifndef STRINGIZER
#define STRINGIZER(arg) #arg
#define STR_VALUE(arg) STRINGIZER(arg)
#endif
#ifndef APATH
#define APATH STR_VALUE(ASSETSPATH)
#endif

SdlImage::SdlImage(SdlWindow &window) : SdlTexture(window) {
    width = 0;
    height = 0;
}

SdlImage::SdlImage(SdlWindow &window, std::string const &path)
    : SdlTexture(window) {
    this->load_from_file(path);
}
SdlImage::SdlImage(SdlWindow &window, BodyType type) : SdlTexture(window) {
    SDL_Color color = getBodyBG(type);
    this->load_from_file(getBodyPath(type), color);
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
    SDL_Color colorDefault = {0xFF, 0xFF, 0xFF};
    load_from_file(path, colorDefault);
}

void SdlImage::load_from_file(std::string const &path, SDL_Color color) {
    this->empty();
    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        throw std::runtime_error("Unable to load image ! SDL_image Error:");
    } else {
        Uint32 map =
            SDL_MapRGB(loadedSurface->format, color.r, color.g, color.b);
        SDL_SetColorKey(loadedSurface, SDL_TRUE, map);

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
    std::string path = APATH;
    switch (type) {
        case NO_BODY_TYPE:
            break;
        case CT1_TYPE:
            break;
        case CT2_TYPE:
            path += std::string("/sprites/ct2.png");
            break;
        case AK47_TYPE:
            path += std::string("/sprites/ak47.png");
            break;
        case AK47_D_TYPE:
            path += std::string("/sprites/ak47_d.png");
            break;
        case OFFICE_TYPE:
            path += std::string("/sprites/office.png");
            break;
        case PLAYER_TYPE:
            path += std::string("/sprites/player.png");
            break;
        case WALL_TYPE:
            path += std::string("/sprites/wall.png");
            break;
        case GLOCK_TYPE:
            path += std::string("/sprites/glock.png");
            break;
        case KNIFE_TYPE:
            path += std::string("/sprites/knife.png");
            break;
        case BOMB_D_TYPE:
            path += std::string("/sprites/bomb_d.png");
            break;
        case TT1_TYPE:
            path += std::string("/sprites/t1.png");
            break;
        case AK47_M_TYPE:
            path += std::string("/sprites/ak47_m.png");
            break;
        case AWP_TYPE:
            path += std::string("/sprites/awp.png");
            break;
        case AWP_M_TYPE:
            path += std::string("/sprites/awp_m.png");
            break;
        case M3_TYPE:
            path += std::string("/sprites/m3.png");
            break;
        case M3_M_TYPE:
            path += std::string("/sprites/m3_m.png");
            break;
        case BOMB_ZONE_TYPE:
            path += std::string("/sprites/bomb_zone.png");
            break;
    }
    return path;
}

SDL_Color SdlImage::getBodyBG(BodyType type) {
    switch (type) {
        case NO_BODY_TYPE:
            break;
        case CT1_TYPE:
            break;
        case CT2_TYPE:
            return WHITE;
            break;
        case AK47_TYPE:
            return WHITE;
            break;
        case AK47_D_TYPE:
            return BLACK;
            break;
        case OFFICE_TYPE:
            return BLACK;
            break;
        case PLAYER_TYPE:
            return WHITE;
            break;
        case WALL_TYPE:
            return WHITE;
            break;
        case GLOCK_TYPE:
            return BLACK;
            break;
        case KNIFE_TYPE:
            return BLACK;
            break;
        case BOMB_D_TYPE:
            return BLACK;
            break;
        case TT1_TYPE:
            return BLACK;
            break;
        case AK47_M_TYPE:
            return PINK;
            break;
        case AWP_TYPE:
            return BLACK;
            break;
        case AWP_M_TYPE:
            return PINK;
            break;
        case M3_TYPE:
            return BLACK;
            break;
        case M3_M_TYPE:
            return PINK;
            break;
        case BOMB_ZONE_TYPE:
            return BLACK;
            break;
    }
    return WHITE;
}

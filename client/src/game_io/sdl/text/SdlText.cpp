#include "game_io/sdl/text/SdlText.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>
#include <utility>

#include "game_io/sdl/SdlSurface.h"

#ifndef STRINGIZER
#define STRINGIZER(arg) #arg
#define STR_VALUE(arg) STRINGIZER(arg)
#endif
#ifndef APATH
#define APATH STR_VALUE(ASSETSPATH)
#endif

SdlText::SdlText(SdlWindow &window, std::string const &text,
                 std::string const &fontname, size_t font_size)
    : font(fontname, font_size), texture(window), text(text), window(&window) {
    pos = {0, 0};
    SdlSurface surf;
    surf = TTF_RenderText_Solid(this->font.font, text.c_str(), GREEN);
    this->texture = surf.transform_to_texture(window);
    this->color = GREEN;
}

SdlText::SdlText(SdlWindow &window, std::string const &text,
                 std::string const &fontname)
    : SdlText(window, text, fontname, 30) {
    this->color = GREEN;
}

SdlText::SdlText(SdlWindow &window, std::string const &text)
    : font(), texture(window), text(text), window(&window) {
    pos = {0, 0};
    SdlSurface surf;
    surf = TTF_RenderText_Solid(this->font.font, text.c_str(), GREEN);
    this->texture = surf.transform_to_texture(window);
    this->color = GREEN;
}
SdlText::SdlText(SdlWindow &window, std::string const &text,
                 SDL_Color const &color, size_t font_size)
    : font(std::string(APATH) + "/font/cs.ttf", font_size),
      texture(window),
      text(text),
      window(&window) {
    pos = {0, 0};
    SdlSurface surf;
    surf = TTF_RenderText_Solid(this->font.font, text.c_str(), color);
    this->texture = surf.transform_to_texture(window);
    this->color = color;
}

SdlText::SdlText(SdlText &&other)
    : font(std::move(other.font)),
      texture(std::move(other.texture)),
      text(std::move(other.text)),
      pos(std::move(other.pos)),
      window(other.window) {
    other.window = nullptr;
}

SdlText &SdlText::operator=(SdlText &&other) {
    if (this == &other) return *this;
    this->font = std::move(other.font);
    this->texture = std::move(other.texture);
    this->text = std::move(other.text);
    this->pos = std::move(other.pos);
    this->window = other.window;
    other.window = nullptr;
    return *this;
}

void SdlText::set_pos(SDL_Point const &pos) { this->pos = pos; }

void SdlText::set_pos(int x, int y) {
    SDL_Point posaux = {x, y};
    this->set_pos(posaux);
}

void SdlText::render() { this->texture.render(pos); }

void SdlText::render(std::string newText) {
    update(newText);
    this->texture.render(pos);
}

const std::string &SdlText::getText() { return text; }

void SdlText::setTexture(std::string const &text) {
    SdlSurface surf;
    surf = TTF_RenderText_Solid(this->font.font, text.c_str(), this->color);

    this->texture = surf.transform_to_texture(*window);
}

SdlText::~SdlText() {}

void SdlText::update(std::string const &text) {}

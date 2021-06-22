#include "game_io/sdl/text/SdlFont.h"

#include <iostream>
#include <stdexcept>
#include <string>

SdlFont::SdlFont(std::string const &fontname, size_t font_size) {
    this->font = TTF_OpenFont(fontname.c_str(), font_size);
    this->check_if_empty();
}

SdlFont::SdlFont(std::string const &fontname) : SdlFont(fontname, 30) {}

SdlFont::SdlFont() : SdlFont("assets/font/cs.ttf") {}

SdlFont::SdlFont(SdlFont &&other) : font(other.font) { other.font = nullptr; }

SdlFont &SdlFont::operator=(SdlFont &&other) {
    if (this == &other) return *this;
    this->font = other.font;
    other.font = nullptr;
    return *this;
}

SdlFont::~SdlFont() { this->empty(); }

void SdlFont::empty() {
    if (font != nullptr) TTF_CloseFont(this->font);
    this->font = nullptr;
}

void SdlFont::check_if_empty() {
    if (this->font == nullptr) {
        std::cout << TTF_GetError() << std::endl;
        throw std::runtime_error("Error, la fuente esta vacia.");
    }
}

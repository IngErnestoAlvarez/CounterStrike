#include "game_io/sdl/text/SdlFont.h"

#include <iostream>
#include <stdexcept>
#include <string>

SdlFont::SdlFont(std::string const &fontname, size_t font_size) {
    this->font = TTF_OpenFont(fontname.c_str(), font_size);
    if (this->font == nullptr) {
        std::cout << TTF_GetError() << std::endl;
        throw std::runtime_error("Error al cargar la fuente");
    }
}

SdlFont::SdlFont(std::string const &fontname) : SdlFont(fontname, 30) {}

SdlFont::SdlFont() : SdlFont("assets/font/cs.ttf") {}

SdlFont::~SdlFont() {}

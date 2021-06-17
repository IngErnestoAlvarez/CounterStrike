#include "game_io/sdl/text/SdlFont.h"

#include <string>

SdlFont::SdlFont(std::string const &fontname, size_t font_size) {
    this->font = TTF_OpenFont(fontname.c_str(), font_size);
}

SdlFont::SdlFont(std::string const &fontname) : SdlFont(fontname, 12) {}

SdlFont::SdlFont() : SdlFont("Sans.ttf") {}

SdlFont::~SdlFont() {}

#include "game_io/sdl/text/SdlText.h"

#include "game_io/sdl/SdlSurface.h"

const SDL_Color WHITE = {255, 255, 255};

SdlText::SdlText(std::string const &text, std::string const &fontname,
                 size_t font_size)
    : font(fontname, font_size), text(text) {
    this->surf = TTF_RenderText_Solid(this->font.font, text.c_str(), WHITE);
}

SdlText::SdlText(std::string const &text, std::string const &fontname)
    : SdlText(text, fontname, 12) {}

SdlText::SdlText(std::string const &text) : font(), text(text) {
    this->surf = TTF_RenderText_Solid(this->font.font, text.c_str(), WHITE);
}

SdlText::~SdlText() {}

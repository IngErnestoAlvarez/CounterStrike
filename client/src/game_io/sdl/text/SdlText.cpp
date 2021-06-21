#include "game_io/sdl/text/SdlText.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "game_io/sdl/SdlSurface.h"

const SDL_Color WHITE = {255, 255, 255};
const SDL_Color GREEN = {50, 205, 50};

// ! HACER LA POSICION DEL TEXTO DENTRO DE ESTA CLASE
SdlText::SdlText(SdlWindow &window, std::string const &text,
                 std::string const &fontname, size_t font_size)
    : font(fontname, font_size), texture(window), text(text) {
    SdlSurface surf;
    surf = TTF_RenderText_Solid(this->font.font, text.c_str(), GREEN);
    this->texture = surf.transform_to_texture(window);
}

SdlText::SdlText(SdlWindow &window, std::string const &text,
                 std::string const &fontname)
    : SdlText(window, text, fontname, 30) {}

SdlText::SdlText(SdlWindow &window, std::string const &text)
    : font(), texture(window), text(text) {
    SdlSurface surf;
    surf = TTF_RenderText_Solid(this->font.font, text.c_str(), GREEN);
    this->texture = surf.transform_to_texture(window);
}

void SdlText::render(SdlWindow &window, SDL_Rect &rect) {
    this->texture.render(window, rect);
}

SdlText::~SdlText() {}

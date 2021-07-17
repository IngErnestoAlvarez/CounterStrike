#ifndef __SDLTEXT_H__
#define __SDLTEXT_H__

#include <string>

#include "game_io/sdl/SdlTexture.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlFont.h"

const SDL_Color WHITE = {255, 255, 255};
const SDL_Color GREEN = {50, 205, 50};
const SDL_Color BLUE = {65, 105, 225};
const SDL_Color RED = {0xbb, 0x0a, 0x1e};

class SdlText {
   private:
    SdlFont font;
    SdlTexture texture;
    std::string text;
    SDL_Point pos;
    SdlWindow *window;
    SDL_Color color;

   public:
    SdlText();
    SdlText(SdlWindow &, std::string const &text);
    SdlText(SdlWindow &, std::string const &text, SDL_Color const &,
            size_t font_size);
    SdlText(SdlWindow &, std::string const &text, std::string const &fontname);
    SdlText(SdlWindow &, std::string const &text, std::string const &fontname,
            size_t font_size);

    SdlText(SdlText const &) = delete;
    SdlText(SdlText &&);

    SdlText &operator=(SdlText const &) = delete;
    SdlText &operator=(SdlText &&);

    void set_pos(int x, int y);
    void set_pos(SDL_Point const &pos);

    void render();
    void render(std::string newText);

    virtual ~SdlText();

    void setTexture(std::string const &text);

   protected:
    virtual void update(std::string const &text);

    const std::string &getText();
};

#endif

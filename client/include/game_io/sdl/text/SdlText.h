#ifndef __SDLTEXT_H__
#define __SDLTEXT_H__

#include <string>

#include "game_io/sdl/SdlTexture.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlFont.h"

class SdlText {
   private:
    SdlFont font;
    SdlTexture texture;
    std::string text;
    SDL_Point pos;
    SdlWindow *window;

   public:
    SdlText();
    SdlText(SdlWindow &, std::string const &text);
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

   protected:
    virtual void update(std::string const &text);

    const std::string &getText();

    void setTexture(std::string const &text);
};

#endif

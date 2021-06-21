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

   public:
    SdlText();
    SdlText(SdlWindow &, std::string const &text);
    SdlText(SdlWindow &, std::string const &text, std::string const &fontname);
    SdlText(SdlWindow &, std::string const &text, std::string const &fontname,
            size_t font_size);

    void render(SdlWindow &window, SDL_Rect &);

    ~SdlText();
};

#endif

#ifndef __SDLTEXT_H__
#define __SDLTEXT_H__

#include <string>

#include "game_io/sdl/SdlSurface.h"
#include "game_io/sdl/text/SdlFont.h"

class SdlText {
   private:
    SdlFont font;
    SdlSurface surf;
    std::string text;

   public:
    SdlText();
    SdlText(std::string const &text);
    SdlText(std::string const &text, std::string const &fontname);
    SdlText(std::string const &text, std::string const &fontname,
            size_t font_size);

    ~SdlText();
};

#endif

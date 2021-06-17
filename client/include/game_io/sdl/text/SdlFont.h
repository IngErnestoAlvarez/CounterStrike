#ifndef __SDLFONT_H__
#define __SDLFONT_H__

#include <SDL2/SDL_ttf.h>

#include <string>

class SdlText;

class SdlFont {
   private:
    TTF_Font *font;

   public:
    SdlFont();
    SdlFont(std::string const &fontname);
    SdlFont(std::string const &fontname, size_t font_size);

    ~SdlFont();

    friend SdlText;
};

#endif

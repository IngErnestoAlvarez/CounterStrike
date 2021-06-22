#ifndef __SDLFONT_H__
#define __SDLFONT_H__

#include <SDL2/SDL_ttf.h>

#include <memory>
#include <string>

class SdlText;

class SdlFont {
   private:
    TTF_Font *font;

   public:
    SdlFont();
    explicit SdlFont(std::string const &fontname);
    SdlFont(std::string const &fontname, size_t font_size);

    explicit SdlFont(SdlFont const &) = delete;
    explicit SdlFont(SdlFont &&);

    SdlFont &operator=(SdlFont const &) = delete;
    SdlFont &operator=(SdlFont &&);

    ~SdlFont();

    friend SdlText;

   private:
    void empty();
    void check_if_empty();
};

#endif

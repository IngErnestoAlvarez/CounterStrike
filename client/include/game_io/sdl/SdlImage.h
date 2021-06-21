#ifndef __SDLIMAGE_H__
#define __SDLIMAGE_H__

#include <string>

#include "game_io/sdl/SdlTexture.h"

class SdlImage : public SdlTexture {
   private:
    int width;
    int height;

   public:
    SdlImage(SdlWindow &window);
    SdlImage(SdlWindow &window, std::string const &path);

    ~SdlImage() override;

    void load_from_file(std::string const &path);
};

#endif

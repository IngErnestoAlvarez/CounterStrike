#ifndef __SDLIMAGE_H__
#define __SDLIMAGE_H__

#include <string>

#include "game_io/sdl/SdlTexture.h"
#include "game_proxy/body_cointainer.h"

class SdlImage : public SdlTexture {
   private:
    int width;
    int height;

   public:
    SdlImage(SdlWindow &window);
    SdlImage(SdlWindow &window, std::string const &path);
    SdlImage(SdlWindow &window, BodyType type);

    SdlImage(SdlImage const &) = delete;
    SdlImage(SdlImage &&);

    SdlImage &operator=(SdlImage const &) = delete;
    SdlImage &operator=(SdlImage &&);

    ~SdlImage() override;

    void load_from_file(std::string const &path);
    void load_from_file(std::string const &path, Uint8 red, Uint8 green,
                        Uint8 blue);

   private:
    std::string getBodyPath(BodyType type);
};

#endif

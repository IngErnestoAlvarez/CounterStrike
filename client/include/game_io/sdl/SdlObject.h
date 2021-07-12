#ifndef __SDLOBJECT_H__
#define __SDLOBJECT_H__

#include <SDL2/SDL.h>

#include <string>

#include "game_io/sdl/SdlImage.h"
#include "game_io/sdl/SdlWindow.h"

class SdlObject {
   protected:
    SdlImage image;
    const int animation_frames;
    SDL_Rect *sprite_clips;
    SDL_Point center;

   public:
    SdlObject(BodyType type, SdlWindow &window);
    SdlObject(std::string const &path, int animation_frames, SdlWindow &window);

    SdlObject(SdlObject const &) = delete;
    SdlObject(SdlObject &&);

    SdlObject &operator=(SdlObject const &) = delete;
    SdlObject &operator=(SdlObject &&);

    virtual ~SdlObject();

    void blend();

    void set_alpha(Uint8 alpha);

    virtual void render(int posx, int posy, float angle);

    virtual void renderAbsolute(int posx, int posy, float angle);

    void setColorMod(Uint8 r, Uint8 g, Uint8 b);
};

#endif

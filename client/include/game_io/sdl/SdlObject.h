#ifndef __SDLOBJECT_H__
#define __SDLOBJECT_H__

#include <SDL2/SDL.h>

#include <string>

#include "game_io/sdl/SdlImage.h"
#include "game_io/sdl/SdlWindow.h"

class SdlObject {
   private:
    SdlImage image;
    SDL_Rect sprite_clips[1];
    SDL_Point pos;
    SDL_Point center;
    const int animation_frames;
    float angle;
    float prevangle;

   public:
    SdlObject(std::string const &path, int animation_frames, SdlWindow &window);

    SdlObject(SdlObject const &) = delete;
    SdlObject(SdlObject &&);

    SdlObject &operator=(SdlObject const &) = delete;
    SdlObject &operator=(SdlObject &&);

    ~SdlObject();

    void set_init_pos(int x, int y);
    void set_init_pos(SDL_Point const &pos);

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    void render();

    void mouse_mov(int x, int y);
};

#endif

#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "game_io/sdl/SdlObject.h"

class Floor : public SdlObject {
   private:
    int width;
    int height;

   public:
    Floor(SdlWindow &window);

    ~Floor();

    void render();
};

#endif

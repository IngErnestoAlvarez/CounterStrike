#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "game_io/sdl/SdlObject.h"
#include "game_logic/map.h"

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

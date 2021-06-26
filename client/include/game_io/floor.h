#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "game_io/sdl/SdlObject.h"
#include "game_logic/map.h"

class Floor : public SdlObject {
   private:
    SdlImage box;
    Map *map;

   public:
    Floor(std::string const &path, int animation_frames, SdlWindow &window,
          Map *map);

    ~Floor();

    void render() override;
};

#endif

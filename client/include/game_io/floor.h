#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "game_io/sdl/SdlObject.h"

class Floor : public SdlObject {
   public:
    Floor(std::string const &path, int animation_frames, SdlWindow &window);

    ~Floor();

    void render() override;
};

#endif

#ifndef __STENCIL_H__
#define __STENCIL_H__

#include "game_io/player.h"
#include "sdl/SdlObject.h"

class Stencil : public SdlObject {
   private:
   public:
    Stencil(SdlWindow &window);
    ~Stencil();

    void mouse_mov(int x, int y) override;
};

#endif  // __STENCIL_H__

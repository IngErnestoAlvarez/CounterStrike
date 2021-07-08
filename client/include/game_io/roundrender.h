#ifndef __ROUNDRENDER_H__
#define __ROUNDRENDER_H__

#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlText.h"

class RoundEnd {
   private:
    SdlText winText;
    SdlText loseText;

   public:
    RoundEnd(SdlWindow &window);
    ~RoundEnd();

    void renderWin();

    void renderLose();
};

#endif  // __ROUNDRENDER_H__

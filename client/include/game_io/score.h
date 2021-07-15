#ifndef __SCORE_H__
#define __SCORE_H__

#include "game_io/sdl/SdlWindow.h"

class Score {
   private:
   public:
    Score(SdlWindow &window);
    ~Score();

    void render();
};

#endif  // __SCORE_H__

#ifndef __FINAL_MATCH_H__
#define __FINAL_MATCH_H__

#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlText.h"

class FinalMatchScreen {
   private:
    // Score
    SdlText winner;
    SdlText looser;

   public:
    FinalMatchScreen(SdlWindow &window);
    ~FinalMatchScreen();

    void render(bool winner);
};

#endif  // __FINAL_MATCH_H__

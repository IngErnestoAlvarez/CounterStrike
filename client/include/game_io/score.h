#ifndef __SCORE_H__
#define __SCORE_H__

#include <vector>

#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlText.h"
#include "game_proxy/final_scores.h"

class Score {
   private:
    std::vector<SdlText> teamAScores;
    std::vector<SdlText> teamBScores;
    SdlWindow *window;

   public:
    Score(SdlWindow &window);
    ~Score();

    void setTeams(std::vector<PlayerScore> &teamA,
                  std::vector<PlayerScore> &teamB);

    void render();
};

#endif  // __SCORE_H__

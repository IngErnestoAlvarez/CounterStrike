#ifndef __FINAL_MATCH_H__
#define __FINAL_MATCH_H__

#include "game_io/score.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlText.h"
#include "game_proxy/final_scores.h"

class FinalMatchScreen {
   private:
    TeamID myTeam;
    Score score;
    SdlText winner;
    SdlText looser;
    FinalScores *fs;

   public:
    FinalMatchScreen(SdlWindow &window, FinalScores *fs, TeamID myTeam);
    ~FinalMatchScreen();

    void render();

    void update(std::vector<PlayerScore> teamA, std::vector<PlayerScore> teamB);
};

#endif  // __FINAL_MATCH_H__

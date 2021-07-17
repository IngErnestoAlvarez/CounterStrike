#ifndef __ROUNDS_H__
#define __ROUNDS_H__

#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/text/SdlText.h"
#include "types.h"

class RoundScore {
   private:
    TeamID myTeam;
    uint8_t myTeamRounds;
    uint8_t otherTeamRounds;
    SdlText myTeamScore;
    SdlText otherTeamScore;

   public:
    RoundScore(SdlWindow &window, TeamID myTeam);

    ~RoundScore();

    void render(uint8_t teamARounds, uint8_t teamBRounds);

   private:
    void update(uint8_t &teamARounds, uint8_t &teamBRounds);
};

#endif  // __ROUNDS_H__

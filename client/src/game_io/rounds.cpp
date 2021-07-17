#include "game_io/rounds.h"

RoundScore::RoundScore(SdlWindow &window, TeamID myTeam)
    : myTeam(myTeam),
      myTeamRounds(0),
      otherTeamRounds(0),
      myTeamScore(window, "0", BLUE, 30),
      otherTeamScore(window, "0", RED, 30) {
    myTeamScore.set_pos(380, 0);
    otherTeamScore.set_pos(420, 0);
}

RoundScore::~RoundScore() {}

void RoundScore::render(uint8_t teamARounds, uint8_t teamBRounds) {
    update(teamARounds, teamBRounds);
    myTeamScore.render();
    otherTeamScore.render();
}

void RoundScore::update(uint8_t &teamARounds, uint8_t &teamBRounds) {
    if (myTeam == TEAM_B) std::swap(teamARounds, teamBRounds);
    // TeamA always my team

    if (myTeamRounds != teamARounds) {
        myTeamRounds = teamARounds;
        myTeamScore.setTexture(std::to_string(myTeamRounds));
    }
    if (otherTeamRounds != teamBRounds) {
        otherTeamRounds = teamBRounds;
        otherTeamScore.setTexture(std::to_string(otherTeamRounds));
    }
}

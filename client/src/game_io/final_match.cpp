#include "game_io/final_match.h"

FinalMatchScreen::FinalMatchScreen(SdlWindow &window, FinalScores *fs,
                                   TeamID myTeam)
    : myTeam(myTeam),
      score(window),
      winner(window, "VICTORIA", BLUE, 60),
      looser(window, "DERROTA", RED, 60),
      fs(fs) {
    winner.set_pos(50, 100);
    looser.set_pos(50, 100);
}

FinalMatchScreen::~FinalMatchScreen() {}

void FinalMatchScreen::update(std::vector<PlayerScore> teamA,
                              std::vector<PlayerScore> teamB) {
    score.setTeams(teamA, teamB);
}

void FinalMatchScreen::render() {
    TeamID winner = fs->getWinnerTeam();
    if (winner == myTeam) {
        this->winner.render();
    } else {
        this->looser.render();
    }
    score.render();
}

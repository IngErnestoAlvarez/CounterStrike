#include "game_io/final_match.h"

FinalMatchScreen::FinalMatchScreen(SdlWindow &window)
    : score(window),
      winner(window, "TU EQUIPO HA GANADO", BLUE, 60),
      looser(window, "TU EQUIPO HA PERDIDO", RED, 60) {
    winner.set_pos(50, 100);
    looser.set_pos(50, 100);
}

FinalMatchScreen::~FinalMatchScreen() {}

void FinalMatchScreen::render(bool winner) {
    if (winner) {
        this->winner.render();
    } else {
        this->looser.render();
    }
    score.render();
}

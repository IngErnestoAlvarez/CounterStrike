#include "game_io/roundrender.h"

RoundEnd::RoundEnd(SdlWindow &window)
    : winText(window, "Ha ganado tu equipo", BLUE, 50),
      loseText(window, "Ha perdido tu equipo", RED, 50) {
    winText.set_pos(100, 300);
    loseText.set_pos(100, 300);
}

RoundEnd::~RoundEnd() {}

void RoundEnd::renderWin() { winText.render(); }

void RoundEnd::renderLose() { loseText.render(); }

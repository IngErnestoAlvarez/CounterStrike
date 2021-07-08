#include "game_io/roundrender.h"

RoundEnd::RoundEnd(SdlWindow &window)
    : winText(window, "¡Ha ganado tu equipo!", BLUE, 50),
      loseText(window, "Ha perdido tu equipo", RED, 50) {}

RoundEnd::~RoundEnd() {}

void RoundEnd::renderWin() { winText.render(); }

void RoundEnd::renderLose() { loseText.render(); }

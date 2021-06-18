#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>

#include <iostream>

#include "game_io/modelo_io.h"
#include "game_logic/modelo_logic.h"

int main(int argc, char const *argv[]) {
    bool jugando = true;
    ModeloLogic juego;
    ModeloIO vista(juego);
    while (jugando) {
        juego.update();
        jugando = vista.update();
    }
    return 0;
}

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <iostream>

#include "sdl/SdlWindow.h"

int main(int argc, char const *argv[]) {
    SdlWindow window(800, 600);
    window.fill();
    window.render();
    SDL_Delay(3000);
    return 0;
}

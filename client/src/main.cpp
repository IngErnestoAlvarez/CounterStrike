#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <iostream>

#include "sdl/SdlWindow.h"
#include "sdl/copy_to_png.h"
#include "sdl/stencil.h"

int main(int argc, char const *argv[]) {
    SdlWindow window(800, 600);
    window.fill();

    Stencil stencil;
    Cpy2Png cpier;

    stencil.make_stencil(window.getRendered());
    cpier.copy_to_png(window.getRendered(), 800, 600);

    window.render();

    SDL_Delay(3000);
    return 0;
}

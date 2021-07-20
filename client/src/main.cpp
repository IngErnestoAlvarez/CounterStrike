#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>

#include <iostream>

#include "app.h"

#define UNEXPECTED_ERROR_ "Ocurrio un error inesperado, disculpe las molestias"

int main(int argc, char const *argv[]) {
    if (argc != 5) {
        return -1;
    }

    try {
        App game(argv[1], argv[2], argv[3], argv[4]);

        game.load_media();

        game.main_loop();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << UNEXPECTED_ERROR_ << std::endl;
    }

    return 0;
}

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>

#include <iostream>

#include "Logger.h"
#include "app.h"

int main(int argc, char const *argv[]) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->enableConsoleLogging();
    log->enaleLog();
    // log->disableLog();
    log->info("Empieza el programa");

    if (argc != 2) {
        log->info("Error en los parametros");
        return -1;
    }

    try {
        App game("localhost", "8000", argv[1]);
        log->info("Loading media");
        game.load_media();
        log->info("Starting main_loop");
        game.main_loop();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    log->info("Termina el programa");
    return 0;
}

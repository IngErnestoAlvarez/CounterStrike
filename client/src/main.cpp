#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>

#include <iostream>

#include "Logger.h"
#include "app.h"

#define UNEXPECTED_ERROR_ "Ocurrio un error inesperado, disculpe las molestias"

int main(int argc, char const *argv[]) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->enableConsoleLogging();
    log->enaleLog();
    // log->disableLog();
    log->info("Empieza el programa");

    if (argc != 4) {
        log->info("Error en los parametros");
        return -1;
    }

    try {
        App game(argv[1], argv[2], argv[3]);

        log->info("Loading media");
        game.load_media();

        log->info("Starting main_loop");
        game.main_loop();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << UNEXPECTED_ERROR_ << std::endl;
    }

    log->info("Termina el programa");
    return 0;
}

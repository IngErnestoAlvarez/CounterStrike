#include <iostream>
#include <string>

#include "Logger.h"
#include "server.h"

#define USAGE "Uso: ./<executable-filepath> <config-filepath> [-debug]"
#define UNEXPECTED_ERROR "Se ha producido un error inesperado"

int main(int argc, char *argv[]) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->enableConsoleLogging();

    if (argc > 3) {
        std::cout << USAGE << std::endl;
        return 1;
    }

    std::string config_filepath = argv[1];
    bool debug = (argc == 3) && (std::string(argv[2]) == std::string("-debug"));

    if (debug) log->enaleLog();

    try {
        log->debug("Comienza el server");
        Server server(argv[1]);
        server.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << UNEXPECTED_ERROR << std::endl;
    }

    return 0;
}

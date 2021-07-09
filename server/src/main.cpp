#include <iostream>

#include "Logger.h"
#include "server.h"

#define USAGE "Uso: ./<executable-filepath> <config-filepath>"
#define UNEXPECTED_ERROR "Se ha producido un error inesperado"

int main(int argc, char *argv[]) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->enableConsoleLogging();
    log->enaleLog();
    // log->disableLog();
    log->debug("Server");

    if (argc != 2) {
        std::cout << USAGE << std::endl;
        return 1;
    }

    try {
        Server server(argv[1]);
        server.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << UNEXPECTED_ERROR << std::endl;
    }

    return 0;
}

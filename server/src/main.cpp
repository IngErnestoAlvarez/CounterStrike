#include <iostream>
#include <string>

#include "server.h"

#define USAGE "Uso: ./<executable-filepath> <config-filepath>"
#define UNEXPECTED_ERROR "Se ha producido un error inesperado"

#ifndef STRINGIZER
#define STRINGIZER(arg) #arg
#define STR_VALUE(arg) STRINGIZER(arg)
#endif
#ifndef CONFIG_PATH
#define CONFIG_PATH STR_VALUE(CONFIGPATH)
#endif

int main(int argc, char *argv[]) {
    if (argc > 3) {
        std::cout << USAGE << std::endl;
        return 1;
    }

    std::string config_filepath = std::string(CONFIG_PATH) + "/config.yaml";

    try {
        Server server(config_filepath);
        server.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << UNEXPECTED_ERROR << std::endl;
    }

    return 0;
}

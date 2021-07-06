#include <iostream>

#include "Logger.h"
#include "server.h"

int main(int argc, char *argv[]) {
    using namespace CPlusPlusLogging;
    Logger *log = Logger::getInstance();
    log->enableConsoleLogging();
    log->info("server");

    Server server;
    server.run();

    char a;
    std::cin >> a;

    return 0;
}

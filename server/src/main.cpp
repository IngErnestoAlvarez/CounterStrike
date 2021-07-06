#include <iostream>

#include "server.h"

int main(int argc, char *argv[]) {
    std::cout << "server" << std::endl;

    Server server;
    server.run();

    char a;
    std::cin >> a;

    return 0;
}

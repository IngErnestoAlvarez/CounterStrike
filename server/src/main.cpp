#include <iostream>
#include "server.h"

int main(int argc, char* argv[]) {
	std::cout << "server" << std::endl;

	Server server;
	server.run();

	return 0;
}

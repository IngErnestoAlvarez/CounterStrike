#include <iostream>

int main(int argc, char** argv) {
    try {
        std::cout << "Counter Strike - Server" << std::endl;
    } catch(std::exception& e) {
    	std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

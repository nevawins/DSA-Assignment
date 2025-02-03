#include "MovieSystem.h"
#include <iostream>

int main() {
    try {
        MovieSystem system;
        system.menu();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) { // catch all handler
        std::cout << "An unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}
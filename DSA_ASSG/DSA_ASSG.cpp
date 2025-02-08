#include <iostream>
#include "MovieSystem.h"

int main() {
    std::cout << "Movie Management System\n";
    std::cout << "----------------------\n";

    MovieSystem movieSystem;
    movieSystem.menu();

    return 0;
}
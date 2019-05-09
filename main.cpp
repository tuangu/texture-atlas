#include <cstddef>
#include <exception>
#include <iostream>

int main() try {
    std::cout << "Hello, world!" << std::endl;

    return 0;
} catch (std::exception &e) {
    std::cerr << e.what();
}
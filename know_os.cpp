#include <iostream>

int main() {
    #if defined(_WIN32) || defined(_WIN64)
        std::cout << "Running on Windows" << std::endl;
    #elif defined(__APPLE__) || defined(__MACH__)
        std::cout << "Running on macOS" << std::endl;
    #elif defined(__linux__)
        std::cout << "Running on Linux" << std::endl;
    #elif defined(__unix__)
        std::cout << "Running on Unix" << std::endl;
    #elif defined(__FreeBSD__)
        std::cout << "Running on FreeBSD" << std::endl;
    #else
        std::cout << "Unknown Operating System" << std::endl;
    #endif

    return 0;
}

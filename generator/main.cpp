#include <iostream>
#include "KeyGenerator.hpp"

int main() {
    uint64_t masterKey = des::KeyGenerator::generateMasterKey();
    std::cout << std::hex << masterKey << std::endl;
    return 0;
}

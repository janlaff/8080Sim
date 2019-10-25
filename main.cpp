#include <iostream>

#include "Cpu.h"

int main() {
    auto cpu = i8080::Cpu();

    cpu.loadProgram({0x3c, 0x3c, 0x3c, 0x07});
    cpu.run(16);
    std::cout << i8080::format("A: %02x\n", cpu.a());

    return 0;
}

#include <iostream>

#include "Cpu.h"

int main() {
    auto cpu = i8080::Cpu();

    cpu.loadProgram({0x06, 0xfa, 0x78});
    cpu.run(100);
    std::cout << std::hex << int(cpu.a()) << std::endl;

    return 0;
}

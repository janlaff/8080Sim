#include <iostream>

#include "Shell.h"

int main() {
    auto cpu = CPU();
    auto shell = Shell(std::cin, std::cout, cpu);

    try {
        while (true) {
            shell.execute(shell.read_line());
        }
    } catch (ExitShell &e) {}

    return 0;
}

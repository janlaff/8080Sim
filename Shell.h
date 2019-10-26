#pragma once

#include <string>

#include "CPU.h"

struct ExitShell {};

class Shell {
public:
    Shell(std::istream& in, std::ostream& out, CPU& cpu);

    std::string read_line() const;
    void execute(std::string command);

    void print_regs();
    void print_byte(uint16_t addr);
    void print_word(uint16_t addr);
    void print_flags();
    void print_stack();
    void print_disassembly();
    void print_help();

private:
    std::istream& m_in;
    std::ostream& m_out;
    CPU& m_cpu;
};
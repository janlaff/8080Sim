#pragma once

#include "Registers.h"
#include "MemoryBus.h"

struct Flags {
    bool sign;
    bool zero;
    bool auxCarry;
    bool parity;
    bool carry;
};

struct CPU {
    MemoryBus bus;
    Registers regs;
    Flags flags;
    uint16_t pc;
    uint16_t sp;
    int cycles;
    bool jump_performed;
    bool int_enable;

    // Update flags
    void update_flags(uint16_t value);
    // Jump
    void jump(uint16_t addr);
    // Read 8 bit parameter
    uint8_t read_d8();
    // Read 16 bit parameter
    uint16_t read_d16();
    // Push value on the stack
    void push(uint16_t value);
    // Pop value from stack
    uint16_t pop();
    // Execute opcode
    void execute(uint16_t opcode);
};
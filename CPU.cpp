#include "CPU.h"
#include "ByteManip.h"
#include "OpcodeImpl.h"

void CPU::jump(uint16_t addr) {
    pc = addr;
    jump_performed = true;
}

uint8_t CPU::read_d8() {
    auto ret = bus.read_byte(pc + 1);
    pc += 1;
    return ret;
}

uint16_t CPU::read_d16() {
    auto ret = join_bytes(bus.read_byte(pc + 2), bus.read_byte(pc + 1));
    pc += 2;
    return ret;
}

void CPU::push(uint16_t value) {
    auto [high, low] = split_bytes(value);
    bus.write_byte(sp - 1, high);
    bus.write_byte(sp - 2, low);
    sp -= 2;
}

uint16_t CPU::pop() {
    auto ret = join_bytes(bus.read_byte(sp + 1), bus.read_byte(sp));
    sp += 2;
    return ret;
}

void CPU::execute(uint16_t opcode) {
    jump_performed = false;
    default_impl[opcode](*this);
}
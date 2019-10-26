#include "MemoryBus.h"

void MemoryBus::write_byte(uint16_t address, uint8_t value) {
    mem[address] = value;
}

uint8_t MemoryBus::read_byte(uint16_t address) {
    return mem[address];
}
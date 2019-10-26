#pragma once

#include <cstdint>

struct MemoryBus {
    uint8_t mem[0x10000];

    void write_byte(uint16_t address, uint8_t value);
    uint8_t read_byte(uint16_t address);
};
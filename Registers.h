#pragma once

#include <cstdint>

struct Registers {
    uint8_t a;
    uint8_t flags;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;

    uint16_t get_psw();
    uint16_t get_bc();
    uint16_t get_de();
    uint16_t get_hl();
    void set_psw(uint16_t value);
    void set_bc(uint16_t value);
    void set_de(uint16_t value);
    void set_hl(uint16_t value);
};
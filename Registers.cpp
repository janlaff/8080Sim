#include "Registers.h"
#include "ByteManip.h"

uint16_t Registers::get_psw() {
    return join_bytes(a, flags);
}

uint16_t Registers::get_bc() {
    return join_bytes(b, c);
}

uint16_t Registers::get_de() {
    return join_bytes(d, e);
}

uint16_t Registers::get_hl() {
    return join_bytes(h, l);
}

void Registers::set_psw(uint16_t value) {
    std::tie(a, flags) = split_bytes(value);
}

void Registers::set_bc(uint16_t value) {
    std::tie(b, c) = split_bytes(value);
}

void Registers::set_de(uint16_t value) {
    std::tie(d, e) = split_bytes(value);
}

void Registers::set_hl(uint16_t value) {
    std::tie(h, l) = split_bytes(value);
}
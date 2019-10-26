#include "ByteManip.h"

uint16_t join_bytes(uint8_t high, uint8_t low) {
    return (high << 8) | low;
}

std::pair<uint8_t, uint8_t> split_bytes(uint16_t value) {
    return { (value >> 8), value & 0xff };
}
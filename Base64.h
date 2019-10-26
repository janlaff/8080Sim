#pragma once

#include <cstdint>

constexpr uint8_t decode_base64(char value) {
    return (value >= 'A' && value <= 'Z') ? (value - 'A' + 0u)
         : (value >= 'a' && value <= 'z') ? (value - 'a' + 26u)
         : (value >= '0' && value <= '9') ? (value - '0' + 52u)
         : (value == '+' ? 62u : 63u);
}

constexpr char encode_base64(uint8_t value) {
    return (value < 26u) ? (value + 'A')
         : (value < 52u) ? (value + 'a' - 26u)
         : (value < 62u) ? (value + '0' - 52u)
         : (value == 62u ? '+' : '/');
}
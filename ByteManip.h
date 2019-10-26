#pragma once

#include <cstdint>
#include <tuple>

uint16_t join_bytes(uint8_t high, uint8_t low);
std::pair<uint8_t, uint8_t> split_bytes(uint16_t value);
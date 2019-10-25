#pragma once

#include <cstdint>

#include "Utility.h"

namespace i8080 {
    using Byte = uint8_t;

    struct Word {
        Byte high;
        Byte low;

        constexpr Word() : high(0), low(0) {}

        constexpr Word(uint16_t value) : high(0), low(0) {
            auto [h, l] = wordSplit(value);
            high = h;
            low = l;
        }

        constexpr Word(Byte high, Byte low) : high(high), low(low) {}

        constexpr operator uint16_t() const {
            return byteJoin(high, low);
        }

        constexpr Word& operator=(uint16_t value) {
            auto [h, l] = wordSplit(value);
            high = h;
            low = l;
            return *this;
        }
    } __attribute__((packed));

    using Address = Word;
}
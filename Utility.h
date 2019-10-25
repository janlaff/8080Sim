#pragma once

#include <cstdint>
#include <tuple>
#include <iostream>

namespace i8080 {
    constexpr uint8_t decodeBase64(char value) {
        return (value >= 'A' && value <= 'Z') ? (value - 'A' + 0u)
             : (value >= 'a' && value <= 'z') ? (value - 'a' + 26u)
             : (value >= '0' && value <= '9') ? (value - '0' + 52u)
             : (value == '+' ? 62u : 63u);
    }

    constexpr char encodeBase64(uint8_t value) {
        return (value < 26u) ? (value + 'A')
             : (value < 52u) ? (value + 'a' - 26u)
             : (value < 62u) ? (value + '0' - 52u)
             : (value == 62u ? '+' : '/');
    }

    constexpr uint16_t byteJoin(uint8_t high, uint8_t low) {
        return (high << 8) | low;
    }

    constexpr std::pair<uint8_t, uint8_t> wordSplit(uint16_t val) {
        return {(val >> 8) & 0xFF, val & 0xFF};
    }

    template<typename T>
    struct format_args {
        static auto convert(T&& value) {
            return std::forward<T>(value);
        }
    };

    template<>
    struct format_args<std::string> {
        static auto convert(const std::string& value) {
            return value.c_str();
        }
    };

    template<typename ... Args>
    std::string format_impl(const char* fmt, Args&&... args) {
        auto len = std::snprintf(nullptr, 0, fmt, std::forward<Args>(args)...);
        auto buf = std::vector<char>(len + 1);

        snprintf(buf.data(), buf.size(), fmt, std::forward<Args>(args)...);
        return std::string(buf.begin(), buf.begin() + len);
    }

    template<typename ... Args>
    std::string format(const std::string& fmt, Args&&... args) {
        return format_impl(fmt.c_str(), format_args<Args>::convert(args)...);
    }
}
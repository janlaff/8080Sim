#pragma once

#include <type_traits>

#include "CPU.h"
#include "Base64.h"
#include "MagicMasks.h"

#define t(pattern) if constexpr(table_match<opcode>(pattern))
#define _t(pattern) if constexpr (false)

/* Clever way of checking if a given mask
 * contains the specified opcode
 */
template<uint8_t opcode>
constexpr bool table_match(const char* pattern) {
    return decode_base64(pattern[opcode / 6]) & ((1 << 5) >> (opcode % 6));
}

template<uint8_t opcode>
constexpr void update_stats(CPU& cpu) {
    cpu.cycles += [&]() constexpr -> int {
        _t("") return 4;
        _t("") return 5;
        _t("") return 7;
        _t("") return 10;
        _t("") return 11;
        _t("") return 13;
        _t("") return 17;
        _t("") return cpu.jump_performed ? 11 : 5; // Maximum correctness ;)
        _t("") return cpu.jump_performed ? 17 : 11;
        else return 0;
    }();
    if (!cpu.jump_performed) cpu.pc++;
}

template<uint8_t opcode>
constexpr void update_flags(CPU& cpu, uint16_t value) {
    auto parity = [](uint8_t val) constexpr {
        uint8_t tmp = 0;

        tmp = val ^ (val >> 1);
        tmp = tmp ^ (tmp >> 2);
        tmp = tmp ^ (tmp >> 4);

        return tmp & 1;
    };

    // Update Z, S, P, AC
    _t() {
        cpu.flags.sign = (value & 0x80) == 0;
        cpu.flags.zero = (value & 0xff) == 0;
        cpu.flags.parity = parity(value);
        cpu.flags.auxCarry = 0; // TODO
    }
    // Update CY
    _t() cpu.flags.carry = (value > 0xff);
}

template<uint8_t opcode>
constexpr uint16_t get_operand(CPU& cpu) {
    _t("") return cpu.read_d8();
    _t("") return cpu.read_d16();
    _t("") return cpu.pop();
    t(mask_operand_a) return cpu.regs.a;
    t(mask_operand_b) return cpu.regs.b;
    t(mask_operand_c) return cpu.regs.c;
    _t("") return cpu.regs.d;
    _t("") return cpu.regs.e;
    _t("") return cpu.regs.h;
    _t("") return cpu.regs.l;
    _t("") return cpu.regs.get_psw();
    _t("") return cpu.regs.get_bc();
    _t("") return cpu.regs.get_de();
    _t("") return cpu.regs.get_hl();
    _t("") return cpu.bus.read_byte(cpu.regs.get_psw());
    _t("") return cpu.bus.read_byte(cpu.regs.get_bc());
    _t("") return cpu.bus.read_byte(cpu.regs.get_de());
    _t("") return cpu.bus.read_byte(cpu.regs.get_hl());
    else return 0;
}

template<uint8_t opcode>
constexpr void store_result(CPU& cpu, uint16_t value) {
    _t("") cpu.bus.write_byte(cpu.read_d16(), value);
    _t("") cpu.push(value);
    _t("") cpu.regs.a = value;
    t(mask_store_b) cpu.regs.b = value;
    _t("") cpu.regs.c = value;
    _t("") cpu.regs.d = value;
    _t("") cpu.regs.e = value;
    _t("") cpu.regs.h = value;
    _t("") cpu.regs.l = value;
    _t("") cpu.regs.set_psw(value);
    _t("") cpu.regs.set_bc(value);
    _t("") cpu.regs.set_de(value);
    _t("") cpu.regs.set_hl(value);
    _t("") cpu.bus.write_byte(cpu.regs.get_bc(), value);
    _t("") cpu.bus.write_byte(cpu.regs.get_de(), value);
    _t("") cpu.bus.write_byte(cpu.regs.get_de(), value);
    _t("") cpu.bus.write_byte(cpu.regs.get_hl(), value);
}

template<uint8_t opcode>
constexpr bool should_jump(CPU& cpu) {
    auto negate_if = [](bool value) constexpr {
        _t("") return !value;
        else return value;
    };

    // Handles jump if (not) flag
    _t("") return negate_if(cpu.flags.sign);
    _t("") return negate_if(cpu.flags.zero);
    _t("") return negate_if(cpu.flags.parity);
    _t("") return negate_if(cpu.flags.carry);
    _t("") return true;
}

template<uint8_t opcode>
constexpr uint16_t do_logic(CPU& cpu, uint16_t operand) {
    uint16_t buffer = 0;

    // Mov instructions
    t(mask_mov) buffer = operand;
    // Inc instructions
    _t("") buffer = operand + 1;
    // Dec instructions
    _t("") buffer = operand - 1;
    // Jump instructions
    _t("") if (should_jump<opcode>(cpu)) cpu.jump(operand);

    return buffer;
}

template<uint8_t opcode>
constexpr void opcode_impl(CPU& cpu) {
    // Fetch operand
    uint16_t operand = get_operand<opcode>(cpu);
    // Do calculations/main part
    uint16_t result = do_logic<opcode>(cpu, operand);
    // Update the required flags
    update_flags<opcode>(cpu, result);
    // Save calculated value
    store_result<opcode>(cpu, result);
    // Increase pc and update cycles
    update_stats<opcode>(cpu);
}

template<uint8_t ... opcodes>
constexpr void(*implemented_opcodes[])(CPU&) = {
    opcode_impl<opcodes>...
};

template<uint8_t ... opcodes>
constexpr auto implement(std::integer_sequence<uint8_t, opcodes...>) {
    return implemented_opcodes<opcodes...>;
}

constexpr auto default_impl = implement(std::make_integer_sequence<uint8_t, 0xff>{});
#pragma once

#include <type_traits>

#include "Definitions.h"
#include "Cpu.h"

// Macros to shorten code
#define t(pattern) if constexpr (table_match<Opcode>(pattern))
#define t_ret(pattern, val) t(pattern) return val
#define t_default(val) else return val

namespace i8080 {
    template<Byte Opcode>
    constexpr bool table_match(const char* pattern) {
        return decodeBase64(pattern[Opcode / 6]) & ((1 << 5) >> (Opcode % 6));
    }

    template<Byte Opcode>
    constexpr Word& getResultWord(Cpu& cpu) {
        t_ret("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQAA", cpu.psw());              // Store result in PSW   // f1
        t_ret("cBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.bc());               // Store result in BC    // 01 02 03 0b
        t_ret("AABwEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.de());               // Store result in DE    // 11 12 13 1b
        t_ret("AEAAQBAwAEAAAAAAAAAAAAAAAAAAAAAAAAAAABAAAAA", cpu.hl());               // Store result in HL    // 09 19 23 2a 2b 39 e3
        t_ret("AAAAAAAAUBAAAAAAAAAAAAAAAAAAAAAABAQEAAQABEA", cpu.sp());               // Store result in SP    // 31 33 3b c5 cd d5 e5 f5 f9
        t_ret("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAMGAgICBAKCA", cpu.pc());               // Store result in PC    // c2 c3 c9 ca d2 da e2 e9 f2 f4 fa
        t_ret("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABAAEAAQABAA", cpu.word(cpu.sp() - 2)); // Store result on stack // c5 d5 e5 f5
        t_ret("AAAAACAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.word(cpu.pc() + 1)); // Store result in mem   // 22
        t_default(cpu.wordNullReg); // Dummy value
    }

    template<Byte Opcode>
    constexpr Byte& getResultByte(Cpu& cpu) {
        t_ret("ASEBIQABAC4AAAAAAAAA//////v///8AAgICAgICAgA", cpu.a());                // Store result in A    // 07 0a 0f 17 1a 1f 2f 3a 3c 3d 3e 78 79 7a 7b 7c 7d 7e 7f 80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f 90 91 92 93 94 95 96 97 98 99 9a 9b 9c 9e 9f a0 a1 a2 a3 a4 a5 a6 a7 a8 a9 aa ab ac ad ae af b0 b1 b2 b3 b4 b5 b6 b7 c6 ce d6 de e6 ee f6
        t_ret("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQAA", cpu.flags());            // Store result in f    // f1
        t_ret("DgAAAAAAAAD/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.b());                // Store result in B    // 04 05 06 40 41 42 43 44 45 46 47
        t_ret("AA4AAAAAAAAA/wAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.c());                // Store result in C    // 0c 0d 0e 48 49 4a 4b 4c 4d 4e 4f
        t_ret("AAAOAAAAAAAAAP8AAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.d());                // Store result in D    // 14 15 16 50 51 52 53 54 55 56 57
        t_ret("AAAADgAAAAAAAAD/AAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.e());                // Store result in E    // 1c 1d 1e 58 59 5a 5b 5c 5d 5e 5f
        t_ret("AAAAAA4AAAAAAAAA/wAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.h());                // Store result in H    // 24 25 26 60 61 62 63 64 65 66 67
        t_ret("AAAAAAAOAAAAAAAAAP8AAAAAAAAAAAAAAAAAAAAAAAA", cpu.l());                // Store result in L    // 2c 2d 2e 68 69 6a 6b 6c 6d 6e 6f
        t_ret("IAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.byte(cpu.bc()));     // Store result in (BC) // 02
        t_ret("AAAgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.byte(cpu.de()));     // Store result in (DE) // 12
        t_ret("AAAAAAAADgAAAAAAAAD9AAAAAAAAAAAAAAAAAAAAAAA", cpu.byte(cpu.hl()));     // Store result in (HL) // 34 35 36 70 71 72 73 74 75 77
        t_ret("AAAAAAAAIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.byte(cpu.pc() + 1)); // Store result in mem  // 32
        t_default(cpu.byteNullReg); // Dummy value
        // TODO add (D16) (BC)...
    }

    template<Byte Opcode>
    constexpr Word& getOperandWord(Cpu& cpu) {
        t_ret("QABAAEAAQAAAAAAAAAAAAAAAAAAAAAAAOCwoKCgoIAA", cpu.word(cpu.pc() + 1)); // D16/adr // 01 11 21 31 c2 c3 c4 ca cc cd d2 d4 da dc e2 e4 ea ec f2
        t_ret("AEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.bc()); // BC // 09
        t_ret("AAAAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.de()); // DE // 19
        t_ret("AAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.hl()); // HL // 29
        t_ret("AAAAAAAAAEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", cpu.sp()); // SP // 39
        t_default(cpu.wordNullReg); // Dummy value
    }

    template<Byte Opcode>
    constexpr Byte& getOperandByte(Cpu& cpu) {
        t_ret("AgICAgICAgIAAAAAAAAAAAAAAAAAAAAAAgISEgICAgI", cpu.byte(cpu.pc() + 1)); // D8   // 06 0e 16 1e 26 2e 36 3e c6 ce d3 d6 db de e6 ee f6 fe
        t_ret("IAAgAAAAIAABAQEBAQEBAQABAQEBAQEBAAAAAAAAAAA", cpu.a());                // A    // 02 12 32 47 4f 57 5f 67 6f 77 7f 8f 97 9f a7 af b7 bf
        t_ret("AAAAAAAAAACAgICAgICAgICAgICAgICAAAAAAAAAAAA", cpu.b());                // B    // 40 48 50 58 60 68 70 78 80 88 90 98 a0 a8 b0 b8
        t_ret("AAAAAAAAAABAQEBAQEBAQEBAQEBAQEBAAAAAAAAAAAA", cpu.c());                // C    // 41 49 51 59 61 69 71 79 81 89 91 99 a1 a9 b1 b9
        t_ret("AAAAAAAAAAAgICAgICAgICAgICAgICAgAAAAAAAAAAA", cpu.d());                // D    // 42 4a 52 5a 62 6a 72 7a 82 8a 92 9a a2 aa b2 ba
        t_ret("AAAAAAAAAAAQEBAQEBAQEBAQEBAQEBAQAAAAAAAAAAA", cpu.e());                // E    // 43 4b 53 5b 63 6b 73 7b 83 8b 93 9b a3 ab b3 bb
        t_ret("AAAAAAAAAAAICAgICAgICAgICAgICAgIAAAAAAAAAAA", cpu.h());                // H    // 44 4c 54 5c 64 6c 74 7c 84 8c 94 9c a4 ac b4 bc
        t_ret("AAAAAAAAAAAEBAQEBAQEBAQEBAQEBAQEAAAAAAAAAAA", cpu.l());                // L    // 45 4d 55 5d 65 6d 75 7d 85 8d 95 9d a5 ad b5 bd
        t_ret("AAAAAAAAAAACAgICAgICAgICAgICAgICAAAAAAAAAAA", cpu.byte(cpu.hl()));     // (HL) // 46 4e 56 5e 66 6e 76 7e 86 8e 96 9e a6 ae b6 be
        t_default(cpu.byteNullReg); // Dummy value
    }

    template<Byte Opcode>
    constexpr Word getInstructionSize() {
        t_ret("AgICAgICAgIAAAAAAAAAAAAAAAAAAAAAAgISEgICAgI", 2u); // 06 0e 16 1e 26 2e 36 3e c6 ce d3 d6 db de e6 ee f6 fe
        t_ret("QABAAGAgYCAAAAAAAAAAAAAAAAAAAAAAODwoLCgsKCw", 3u); // 01 11 21 22 2a 31 32 3a c2 c3 c4 ca cb cc cd d2 d4 da dc dd e2 e4 ea ec ed f2 f4 fa fc fd
        t_default(1u);
    }

    template<Byte Opcode>
    constexpr unsigned int getInstructionCycles() {
        t_ret("gIGAgYCBgIAAAQAAAAAAAP39/f39/f39AAAAAAAAEBA", 4);  // 00 08 0f 10 18 1f 20 28 2f 30 38 4f 80 81 82 83 84 85 87 88 89 8a 8b 8c 8d 8f 90 91 92 93 94 95 97 98 99 9a 9b 9c 9d 9f a0 a1 a2 a3 a4 a5 a7 a8 a9 aa ab ac ad af b0 b1 b2 b3 b4 b5 b7 b8 b9 ba bb bc bd bf f3 fb
        t_ret("HBwcHBwcHBz9/f39/f39/QAAAAAAAAAAAAAAAAAAAAA", 5);  // 03 04 05 0b 0c 0d 13 14 15 1b 1c 1d 23 24 25 2b 2c 2d 33 34 35 3b 3c 3d 40 41 42 43 44 45 47 48 49 4a 4b 4c 4d 4f 50 51 52 53 54 55 57 58 59 5a 5b 5c 5d 5f 60 61 62 63 64 65 67 68 69 6a 6b 6c 6d 6f 70 71 72 73 74 75 77 78 79 7a 7b 7c 7d 7f
        t_ret("IiIiIgICAgICAgICAgL/AgICAgICAgICAgICAgICAgI", 7);  // 02 6 a e 12 16 1a 1e 26 2e 36 3e 46 4e 56 5e 66 6e 70 71 72 73 74 75 76 76 77 7e 86 8e 96 9e a6 ae b6 be c6 ce d6 de e6 ee f6 fe
        t_ret("QEBAQEBATkAAAAAAAAAAAAAAAAAAAAAAcHBwcGAgYCA", 10); // 01 09 11 19 21 29 31 34 35 36 39 c1 c2 c3 c9 ca cb d1 d2 d3 d9 da db e1 e2 ea f1 f2 fa
        t_ret("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABQEFAQUBBQE", 11); // c5 c7 cf d5 d7 df e5 e7 ef f5 f7 ff
        t_ret("AAAAAAAAICAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 13); // 32 3a
        t_ret("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAwADAAMAAw", 17); // cc cd dc dd ec ed fc fd
        t_default(0);
    }

    template<Byte Opcode>
    constexpr unsigned int implementInstruction(Cpu& cpu) {
        // Result 16 Bit
        Word& resultWord = getResultWord<Opcode>(cpu);
        // Result 8 Bit
        Byte& resultByte = getResultByte<Opcode>(cpu);
        // Operand 16 Bit
        Word& operandWord = getOperandWord<Opcode>(cpu);
        // Operand 8 Bit
        Byte& operandByte = getOperandByte<Opcode>(cpu);

        /*
         * Instruction implementations
        */

        // 8 bit group

        // B8 <- B8 // 02 06 0a 0e 12 16 1a 1e 26 2e 32 3a 3e 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f 50 51 52 53 54 55 56 57 58 59 5a 5b 5c 5d 5e 5f 60 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f 70 71 72 73 74 75 77 78 79 7a 7b 7c 7d 7e 7f
        t("IiIiIgICICL////////9/wAAAAAAAAAAAAAAAAAAAAA") {
            resultByte = operandByte;
        }
        // B8++ // 04 0c 14 1c 24 2c 34 3c
        t("CAgICAgICAgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA") {
            resultByte = resultByte + 1;
        }
        // B8-- // 05 0d 15 1d 25 2d 35 3d
        t("BAQEBAQEBAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA") {
            resultByte = resultByte - 1;
        }
        // B8 += B8 // 80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f
        t("AAAAAAAAAAAAAAAAAAAAAP//AAAAAAAAAAAAAAAAAAA") {
            resultByte = resultByte + operandByte;
        }
        // B8 += B8 + |CY| Additions // 88 89 8a 8b 8c 8d 8e 8f
        t("AAAAAAAAAAAAAAAAAAAAAAD/AAAAAAAAAAAAAAAAAAA") {
            resultByte = resultByte + cpu.getFlags().carry;
        }
        // B8 -= B8 // 90 91 92 93 94 95 96 97 98 99 9a 9b 9c 9d 9e 9f
        t("AAAAAAAAAAAAAAAAAAAAAAAA//8AAAAAAAAAAAAAAAA") {
            resultByte = resultByte - operandByte;
        }
        // B8 -= B8 - |CY| Additions // 98 99 9a 9b 9c 9d 9e 9f
        t("AAAAAAAAAAAAAAAAAAAAAAAAAP8AAAAAAAAAAAAAAAA") {
            resultByte = resultByte - cpu.getFlags().carry;
        }

        // 16 bit group

        // B16 <- B16 // 01 11 21 31
        t("QABAAEAAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA") {
            resultWord = operandWord;
        }
        // B16 += B16 // 09 19 29 39
        t("AEAAQABAAEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA") {
            resultWord = resultWord + operandWord;
        }
        // B16++ // 03 13 23 33
        t("EAAQABAAEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA") {
            resultWord = resultWord + 1;
        }
        // B16-- // 0b 1b 2b 3b
        t("ABAAEAAQABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA") {
            resultWord = resultWord - 1;
        }

        // Bit shifting group

        // RLC // 07
        t("AQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA") {
            uint16_t tmp = (resultByte << 1 | resultByte >> 7);
            cpu.getFlags().carry = (resultByte >> 7) & 1;
            resultByte = tmp;
        }
        // RRC // 0f
        t("AAEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA") {
            uint16_t tmp = (resultByte >> 1 | resultByte << 7);
            cpu.getFlags().carry = (resultByte & 0x1);
            resultByte = tmp;
        }

        // TODO: implement remaining instructions

        // Increment pc
        cpu.pc() = cpu.pc() + getInstructionSize<Opcode>();

        // TODO: implement jumps here, after pc increment to override value

        // Return cpu cycles
        return getInstructionCycles<Opcode>();
    }

    template<Byte ... Opcodes>
    constexpr unsigned int(*implementInstructions[])(Cpu& cpu) = {
        implementInstruction<Opcodes>...
    };

    template<Byte ... Opcodes>
    constexpr auto expand(std::integer_sequence<Byte, Opcodes...>) {
        return implementInstructions<Opcodes...>;
    }

    constexpr auto instructions = expand(std::make_integer_sequence<Byte, std::numeric_limits<Byte>::max()>{});
}
#pragma once

#include <tuple>
#include <vector>

#include "Definitions.h"

namespace i8080 {
    struct CpuFlags {
        uint8_t sign : 1;
        uint8_t zero : 1;
        uint8_t : 1;
        uint8_t auxCarry : 1;
        uint8_t : 1;
        uint8_t parity : 1;
        uint8_t : 1;
        uint8_t carry : 1;
    };

    enum {
        R_PSW = 0,
        R_BC,
        R_DE,
        R_HL,
        R_SP,
        R_PC,
        R_COUNT,
    };

    class Cpu {
    public:
        // Register dummies for default values, avoids pointer usage
        static Byte byteNullReg;
        static Word wordNullReg;

        Cpu();

        void run(unsigned int cycles);
        void loadProgram(const std::vector<Byte>& program);
        Byte readByte(Address addr);
        Word readWord(Address addr);
        void writeByte(Address addr, Byte val);
        void writeWord(Address addr, Word val);
        void updateFlags(Word value);
        unsigned int execute(Byte opcode);

        // Mem getter/setter
        Byte& byte(Address addr);
        Word& word(Address addr);

        // Register getter/setter
        Byte& a();
        Byte& flags();
        Byte& b();
        Byte& c();
        Byte& d();
        Byte& e();
        Byte& h();
        Byte& l();
        Word& psw();
        Word& bc();
        Word& de();
        Word& hl();
        Word& sp();
        Word& pc();

    private:
        Word m_regs[R_COUNT];
        Byte m_mem[65536];
        CpuFlags m_flags;
    };
}
#include "Cpu.h"

#include "Utility.h"
#include "Instructions.h"

#include <algorithm>

namespace i8080 {
    Byte Cpu::byteNullReg;
    Word Cpu::wordNullReg;

    Cpu::Cpu() {}

    void Cpu::run(unsigned int cycles) {
        auto executedCycles = 0ul;

        while (executedCycles < cycles) {
            executedCycles += execute(byte(pc()));
        }
    }

    void Cpu::loadProgram(const std::vector<Byte> &program) {
        std::copy_n(program.cbegin(), std::min(program.size(), 65536ul), &m_mem[0]);
    }

    Byte Cpu::readByte(Address addr) {
        return m_mem[addr];
    }

    Word Cpu::readWord(Address addr) {
        // TODO: check memory order
        return byteJoin(readByte(addr), readByte(addr + 1));
    }

    void Cpu::writeByte(Address addr, Byte val) {
        m_mem[addr] = val;
    }

    void Cpu::writeWord(Address addr, Word val) {
        // TODO: check memory order
        auto [high, low] = wordSplit(val);
        writeByte(addr, high);
        writeByte(addr + 1, low);
    }

    void Cpu::updateFlags(Word value) {
        auto calcParity = [](Byte val) {
            Byte tmp = 0;

            tmp = val ^ (val >> 1);
            tmp = tmp ^ (tmp >> 2);
            tmp = tmp ^ (tmp >> 4);

            return tmp & 1;
        };

        m_flags.zero = (value & 0xff) == 0;
        m_flags.sign = (value & 0x80) == 0;
        m_flags.parity = calcParity(value & 0xff);
        m_flags.carry = (value > 0xff);
        m_flags.auxCarry = 0; // TODO
    }

    unsigned int Cpu::execute(Byte opcode) {
        return instructions[opcode](*this);
    }

    CpuFlags& Cpu::getFlags() {
        return m_flags;
    }

    Byte& Cpu::byte(Address addr) {
        return m_mem[addr];
    }

    Word& Cpu::word(Address addr) {
        return reinterpret_cast<Word&>(m_mem[addr]);
    }

    Byte& Cpu::a() {
        return m_regs[R_PSW].high;
    }

    Byte& Cpu::flags() {
        return reinterpret_cast<Byte&>(m_flags);
    }

    Byte& Cpu::b() {
        return m_regs[R_BC].high;
    }

    Byte& Cpu::c() {
        return m_regs[R_BC].low;
    }

    Byte& Cpu::d() {
        return m_regs[R_DE].high;
    }

    Byte& Cpu::e() {
        return m_regs[R_DE].low;
    }

    Byte& Cpu::h() {
        return m_regs[R_HL].high;
    }

    Byte& Cpu::l() {
        return m_regs[R_HL].low;
    }

    Word& Cpu::psw() {
        return m_regs[R_PSW];
    }

    Word& Cpu::bc() {
        return m_regs[R_BC];
    }

    Word& Cpu::de() {
        return m_regs[R_DE];
    }

    Word& Cpu::hl() {
        return m_regs[R_HL];
    }

    Word& Cpu::sp() {
        return m_regs[R_SP];
    }

    Word& Cpu::pc() {
        return m_regs[R_PC];
    }
}
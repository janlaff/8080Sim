#include "Shell.h"

#include <sstream>
#include <iterator>
#include <vector>

unsigned int parse_hex_string(const char* str, unsigned int value = 0) {
    auto val = std::tolower(*str);

    auto isHexDigit = ('0' <= val <= '9') || ('a' <= val <= 'f');
    auto hexVal = ('0' <= val <= '9') ? (val - '0')
                                      : ('a' <= val <= 'f') ? (val - 'a' + 10)
                                                            : 0;

    if (val) {
        if (isHexDigit) {
            return parse_hex_string(str + 1, hexVal + 16 * value);
        } else {
            throw std::runtime_error("Failed to parse hex string");
        }
    } else {
        return value;
    }
}

template<typename T>
struct format_args {
    static auto convert(T value) {
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
std::string format_impl(const char* fmt, Args... args) {
    auto len = std::snprintf(nullptr, 0, fmt, std::forward<Args>(args)...);
    auto buf = std::vector<char>(len + 1);

    snprintf(buf.data(), buf.size(), fmt, std::forward<Args>(args)...);
    return std::string(buf.begin(), buf.begin() + len);
}

template<typename ... Args>
std::string format(const std::string& fmt, Args... args) {
    return format_impl(fmt.c_str(), format_args<Args>::convert(args)...);
}

Shell::Shell(std::istream &in, std::ostream &out, CPU &cpu)
    : m_in(in), m_out(out), m_cpu(cpu) {}

std::string Shell::read_line() const {
    m_out << "> ";
    m_out.flush();

    std::string tmp;
    std::getline(m_in, tmp);
    return tmp;
}

void Shell::execute(std::string command) {
    m_out << format("[Command received: (%s)]", command) << std::endl;

    // Split string
    auto splitted = std::vector<std::string>();
    auto iss = std::istringstream(command);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(splitted));

    auto numToken = splitted.size();
    m_out << format("[Token: (%d)]", numToken) << std::endl;

    if (numToken == 0) {
        print_help();
    } else {
        auto cmd = splitted[0];

        if (cmd == "exit") {
            throw ExitShell();
        }
        else if (cmd == "reg") {
            //printRegs();
        }
        else if (cmd == "flag") {
            //printFlags();
        }
        else if (cmd == "rb" && numToken == 2) {
            print_byte(parse_hex_string(splitted[1].c_str()));
        }
        else if (cmd == "rw" && numToken == 2) {
            print_word(parse_hex_string(splitted[1].c_str()));
        }
        else if (cmd == "wb" && numToken == 3) {
            m_cpu.bus.write_byte(parse_hex_string(splitted[1].c_str()), parse_hex_string(splitted[2].c_str()));
        }
        else if (cmd == "x" && numToken == 3) {
            auto opcode = parse_hex_string(splitted[1].c_str());
            m_cpu.execute(opcode);
        }
        else {
            print_help();
        }
    }
}

void Shell::print_byte(uint16_t addr) {
    m_out << format("[0x%04x] = %02x", addr, m_cpu.bus.read_byte(addr)) << std::endl;
}

void Shell::print_word(uint16_t addr) {
    //m_out << format("[0x%04x] = %04x", addr, m_cpu.bus.read_byte(addr)) << std::endl;
}

void Shell::print_help() {
    m_out << "HELP PAGE HERE" << std::endl;
}
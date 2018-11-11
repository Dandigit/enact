//
// Created by dan on 9/11/18.
//

#ifndef GVM_CHUNK_H
#define GVM_CHUNK_H

#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>

#include "common.h"

typedef std::pair<index_t, line_t> indexLine_t;

namespace OpCode {
    enum OpCode {
        CONSTANT,
        CONSTANT_LONG,
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        MODULUS,
        NEGATE,
        RETURN,
    };
}

struct DisassembledChunk {
    std::string str;
    index_t offset;
};

class Chunk {
private:
    std::vector<uint8_t> m_code;
    std::vector<double> m_values;

    std::unordered_map<index_t, line_t> m_lines;
    line_t m_lastLine = 0;

    index_t addConstant(double value);

public:
    Chunk() = default;

    void write(uint8_t byte, line_t line);
    void writeConstant(double value, line_t line);

    const std::vector<uint8_t>& code() const;
    const std::vector<double>& values() const;

    line_t getLine(index_t index) const;

    DisassembledChunk disassembleInstruction(index_t index) const;
    std::string disassemble() const;
};

void writeShiftedIndex(std::vector<uint8_t> &data, index_t index);
uint32_t unshiftBytes(uint8_t one, uint8_t two, uint8_t three);

#endif //GVM_CHUNK_H
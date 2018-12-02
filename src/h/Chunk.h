//
// Created by dan on 9/11/18.
//

#ifndef MATILDA_CHUNK_H
#define MATILDA_CHUNK_H

#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>

#include "common.h"
#include "Value.h"

typedef std::pair<index_t, line_t> indexLine_t;

namespace OpCode {
    enum OpCode {
        CONSTANT,
        CONSTANT_LONG,

        TRUE,
        FALSE,
        NIL,

        EQUAL,
        GREATER,
        LESS,

        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        MODULUS,

        CONDITIONAL,

        NEGATE,
        NOT,

        POP,

        CALL,

        DEFINE_GLOBAL_VARIABLE,
        DEFINE_GLOBAL_CONSTANT,
        GET_GLOBAL,
        SET_GLOBAL,

        PRINT,

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
    std::vector<Value> m_values;

    std::unordered_map<index_t, line_t> m_lines;
    line_t m_lastLine = 0;

    index_t addConstant(Value value);

public:
    Chunk() = default;

    void write(uint8_t byte, line_t line);
    void writeConstant(Value value, line_t line);

    const std::vector<uint8_t>& code() const;
    const std::vector<Value>& values() const;

    line_t getLine(index_t index) const;

    DisassembledChunk disassembleInstruction(index_t index) const;
    std::string disassemble() const;
};

void writeShiftedIndex(std::vector<uint8_t> &data, index_t index);
uint32_t unshiftBytes(uint8_t one, uint8_t two, uint8_t three);

#endif //MATILDA_CHUNK_H

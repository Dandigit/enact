#include <iomanip>
#include <sstream>

#include "h/Chunk.h"

// private =>

index_t Chunk::addConstant(Value value) {
    m_values.push_back(value);
    return m_values.size() - 1;
}

// <= private

// public =>

void Chunk::write(uint8_t byte, line_t line) {
    if (line != m_lastLine) {
        m_lastLine = line;
        m_lines.insert(indexLine_t(m_code.size(), line));
    }
    m_code.push_back(byte);
}

void Chunk::writeConstant(Value value, line_t line) {
    index_t valueIndex = addConstant(value);

    if (valueIndex < 256) {
        write(OpCode::CONSTANT, line);
        write(((uint8_t) valueIndex), line);
    } else {
        write(OpCode::CONSTANT_LONG, line);
        write((uint8_t)(valueIndex & 0xff), line);
        write((uint8_t)((valueIndex >> 8) & 0xff), line);
        write((uint8_t)((valueIndex >> 16) & 0xff), line);
    }
}

line_t Chunk::getLine(index_t index) const {
    if (m_lines.count(index) != 0) {
        return m_lines.at(index);
    }

    return getLine(index - 1);
}

DisassembledChunk Chunk::disassembleInstruction(index_t index) const {
    std::stringstream stream;
    stream << std::setfill('0');

    uint8_t byte = m_code[index];
    line_t line = getLine(index);

    stream << std::setw(4) << index;

    if (index > 0 && line == getLine(index - 1)) {
        stream << "     | ";
    } else {
        stream << "    " << getLine(index) << " ";
    }

    switch (byte) {
        case OpCode::CONSTANT:
            ++index;
            stream << "CONSTANT        "
                   << (int)(m_code[index]) << " '" << m_values[((int)m_code[index])] << "'";
            break;
        case OpCode::CONSTANT_LONG: {
            uint32_t valueIndex = m_code[index + 1] |
                    (m_code[index + 2] << 8) |
                    (m_code[index + 3] << 16);
            index += 3;
            stream << "CONSTANT_LONG   "
                        << (int)valueIndex << " '" << m_values[(int)valueIndex] << "'";
            break;
        }

        case OpCode::TRUE: stream << "TRUE"; break;
        case OpCode::FALSE: stream << "FALSE"; break;
        case OpCode::NIL: stream << "NIL"; break;
        case OpCode::EQUAL: stream << "EQUAL"; break;
        case OpCode::GREATER: stream << "GREATER"; break;
        case OpCode::LESS: stream << "LESS"; break;
        case OpCode::ADD: stream << "ADD"; break;
        case OpCode::SUBTRACT: stream << "SUBTRACT"; break;
        case OpCode::MULTIPLY: stream << "MULTIPLY"; break;
        case OpCode::DIVIDE: stream << "DIVIDE"; break;
        case OpCode::MODULUS: stream << "MODULUS"; break;
        case OpCode::CONDITIONAL: stream << "CONDITIONAL"; break;
        case OpCode::NEGATE: stream << "NEGATE"; break;
        case OpCode::NOT: stream << "NOT"; break;
        case OpCode::RETURN: stream << "RETURN"; break;
    }

    stream << "\n";
    return {stream.str(), index};
}

std::string Chunk::disassemble() const {
    std::stringstream chunkString;
    chunkString << std::setfill('0');

    for (int i = 0; i < m_code.size(); ++i) {
        DisassembledChunk result = disassembleInstruction(i);
        chunkString << result.str;
        i = result.offset;
    }

    std::string s = chunkString.str();
    return chunkString.str();
}

const std::vector<uint8_t>& Chunk::code() const { return m_code; }
const std::vector<Value>& Chunk::values() const { return m_values; }

// <= public

uint32_t unshiftBytes(uint8_t one, uint8_t two, uint8_t three) {
    return (one | (two << 8) | (three << 16));
}
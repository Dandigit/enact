#ifndef GVM_VM_H
#define GVM_VM_H

#include "Chunk.h"

#define MAX_PUSHES_PER_INSTRUCTION 1

enum class InterpretResult {
    OK,
    STATIC_ERROR,
    RUNTIME_ERROR,
};

class VM {
private:
    const Chunk &m_chunk;
    std::vector<double> m_stack;
    index_t m_stackTop;

    const std::vector<uint8_t> &m_ip;
    const std::vector<double> &m_values;

    double peek(int distance) const;
public:
    explicit VM(const Chunk &chunk);

    InterpretResult run();

    // Stack operations
    void push(double value);
    double pop();
};

#endif //GVM_VM_H

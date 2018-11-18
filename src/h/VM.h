#ifndef GVM_VM_H
#define GVM_VM_H

#include "Chunk.h"
#include "Value.h"

#define MAX_PUSHES_PER_INSTRUCTION 1

enum class InterpretResult {
    OK,
    COMPILE_ERROR,
    STATIC_ERROR,
    RUNTIME_ERROR,
};

class VM {
private:
    const Chunk &m_chunk;
    std::vector<Value> m_stack;
    index_t m_stackTop;

    const std::vector<uint8_t> &m_ip;
    const std::vector<Value> &m_values;

    index_t m_currentInstruction;

    void resetStack();

    Value peek(int distance) const;
public:
    explicit VM(const Chunk &chunk);

    void runtimeError(const std::string &message);

    InterpretResult run();

    // Stack operations
    void push(Value value);
    Value pop();
};

#endif //GVM_VM_H

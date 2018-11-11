#include "h/VM.h"

#define DEBUG_TRACE_EXECUTION

#ifdef DEBUG_TRACE_EXECUTION
#include <iostream>
#endif

VM::VM(const Chunk &chunk) : m_chunk { chunk }, m_stackTop{ 0 }, m_ip{ chunk.code() }, m_values{ chunk.values() } {
    m_stack.resize(chunk.code().size() * MAX_PUSHES_PER_INSTRUCTION);
}

void checkNumberOperands(double a, double b) {
    if (false) {

    }
}

InterpretResult VM::run() {
#define BINARY_OP(op) \
    do { \
        checkNumberOperands(peek(0), peek(1)); \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while (false)

    for (int i = 0; i < m_ip.size(); ++i) {
#ifdef DEBUG_TRACE_EXECUTION
        std::cout << "    ";
        for (int stackIndex = 0; stackIndex < m_stackTop; ++stackIndex) {
            std::cout << "[" << m_stack[stackIndex] << "] ";
        }
        std::cout << "\n" << m_chunk.disassembleInstruction(i).str;
#endif
        switch (m_ip[i]) {
            case OpCode::CONSTANT:
                push(m_values[m_ip[++i]]);
                break;
            case OpCode::CONSTANT_LONG:
                push(m_values[unshiftBytes(m_ip[i + 1], m_ip[i + 2], m_ip[i + 3])]);
                i += 3;
                break;
            case OpCode::ADD: BINARY_OP(+); break;
            case OpCode::SUBTRACT: BINARY_OP(-); break;
            case OpCode::MULTIPLY: BINARY_OP(*); break;
            case OpCode::DIVIDE: BINARY_OP(/); break;
            case OpCode::MODULUS: {
                double b = pop();
                double a = pop();
                push((double)((int)a % (int)b));
                break;
            }
            case OpCode::NEGATE:
                push(-pop());
                break;
            case OpCode::RETURN:
                return InterpretResult::OK;

        }
    }
#undef BINARY_OP
}

void VM::push(double value) {
    m_stack[m_stackTop++] = value;
}

double VM::pop() {
    return m_stack[--m_stackTop];
}

double VM::peek(int distance) const {
    return m_stack[m_stackTop - 1 - distance];
}
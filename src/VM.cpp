#include "h/VM.h"

#define DEBUG_TRACE_EXECUTION

#ifdef DEBUG_TRACE_EXECUTION
#include <iostream>
#endif

VM::VM(const Chunk &chunk) : m_chunk { chunk }, m_stackTop{ 0 }, m_ip{ chunk.code() }, m_values{ chunk.values() } {
    m_stack.resize(chunk.code().size() * MAX_PUSHES_PER_INSTRUCTION);
}

InterpretResult VM::run() {
#define BINARY_OP(op) \
    do { \
        if (!peek(0).isNumber() || !peek(1).isNumber()) { \
            runtimeError("Operands must be numbers."); \
            return InterpretResult::RUNTIME_ERROR; \
        } \
        double b = pop().asNumber(); \
        double a = pop().asNumber(); \
        push(Value{a op b}); \
    } while (false)

    for (int i = 0; i < m_ip.size(); ++i) {
        m_currentInstruction = i;
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
            case OpCode::TRUE: push(Value{true}); break;
            case OpCode::FALSE: push(Value{false}); break;
            case OpCode::NIL: push(Value{}); break;
            case OpCode::EQUAL: {
                Value b = pop();
                Value a = pop();
                push(Value{a == b});
                break;
            }
            case OpCode::GREATER: BINARY_OP(>); break;
            case OpCode::LESS: BINARY_OP(<); break;
            case OpCode::ADD: BINARY_OP(+); break;
            case OpCode::SUBTRACT: BINARY_OP(-); break;
            case OpCode::MULTIPLY: BINARY_OP(*); break;
            case OpCode::DIVIDE: BINARY_OP(/); break;
            case OpCode::MODULUS: {
                if (!peek(0).isNumber() || !peek(1).isNumber()) { \
                    runtimeError("Operands must be numbers.");
                    return InterpretResult::RUNTIME_ERROR;
                }
                double b = pop().asNumber();
                double a = pop().asNumber();
                push(Value{(double)((int)a % (int)b)});
                break;
            }
            case OpCode::NEGATE:
                if (!peek(0).isNumber()) {
                    runtimeError("Operand must be a number.");
                    return InterpretResult::RUNTIME_ERROR;
                }
                push(Value{-pop().asNumber()});
                break;
            case OpCode::NOT:
                push(Value{pop().isFalsey()});
                break;
            case OpCode::RETURN:
                return InterpretResult::OK;

        }
    }
#undef BINARY_OP
}

void VM::runtimeError(const std::string &message) {
    std::cout << message << "\n[line " << m_chunk.getLine(m_currentInstruction) << "]\n";
}

void VM::push(Value value) {
    m_stack[m_stackTop++] = value;
}

Value VM::pop() {
    return m_stack[--m_stackTop];
}

Value VM::peek(int distance) const {
    return m_stack[m_stackTop - 1 - distance];
}
#include "h/VM.h"
#include "h/Parser.h"

#define DEBUG_TRACE_EXECUTION

#ifdef DEBUG_TRACE_EXECUTION
#include <iostream>
#endif

VM::VM() :
        m_chunk{ nullptr },
        m_stackTop{ 0 },
        m_ip{ nullptr },
        m_values{ nullptr } {
}

InterpretResult VM::run(const Chunk &chunk) {
    m_chunk = &chunk;
    m_ip = &m_chunk->code();
    m_values = &m_chunk->values();

    m_stack.resize(m_ip->size() * MAX_PUSHES_PER_INSTRUCTION);

    InterpretResult result = execute();
    resetStack();
    return result;
}

InterpretResult VM::execute() {
#define READ_BYTE() ((*m_ip)[m_currentInstruction++])
#define READ_CONSTANT() ((*m_values)[READ_BYTE()])
#define READ_CONSTANT_LONG() ((*m_values)[unshiftBytes(READ_BYTE(), READ_BYTE(), READ_BYTE())])

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

    m_currentInstruction = 0;
    while (true) {
#ifdef DEBUG_TRACE_EXECUTION
        std::cout << "    ";
        for (int stackIndex = 0; stackIndex < m_stackTop; ++stackIndex) {
            std::cout << "[" << m_stack[stackIndex] << "] ";
        }
        DisassembledChunk disassembled = m_chunk->disassembleInstruction(m_currentInstruction);
        std::cout << "\n" << disassembled.str;
#endif

        switch (READ_BYTE()) {
            case OpCode::CONSTANT:
                push(READ_CONSTANT());
                break;
            case OpCode::CONSTANT_LONG:
                push(READ_CONSTANT_LONG());
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
            case OpCode::ADD: {
                if (peek(0).isNumber() && peek(1).isNumber()) {
                    double b = pop().asNumber();
                    double a = pop().asNumber();
                    push(Value{a + b});
                } else if (peek(0).isObject() && peek(1).isObject() &&
                            peek(0).asObject()->isString() && peek(1).asObject()->isString()) {
                    StringObject *b = pop().asObject()->asString();
                    StringObject *a = pop().asObject()->asString();
                    StringObject *result = Allocator::makeStringObject((*a + *b).asStdString());
                    push(Value{result});
                } else {
                    runtimeError("Operands must be two numbers or two strings.");
                    return InterpretResult::RUNTIME_ERROR;
                }
                break;
            }
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
            case OpCode::CONDITIONAL: {
                Value elseBranch = pop();
                Value thenBranch = pop();
                Value condition = pop();

                push(condition.isTruthy() ? thenBranch : elseBranch);
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
            case OpCode::POP:
                pop();
                break;
            case OpCode::PRINT:
                std::cout << pop() << "\n";
                break;
            case OpCode::RETURN:
                return InterpretResult::OK;

        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
#undef READ_CONSTANT_LONG
#undef BINARY_OP
}

void VM::runtimeError(const std::string &message) {
    std::cerr << message << "\n[line " << m_chunk->getLine(m_currentInstruction) << "]\n";
    resetStack();
}

void VM::resetStack() {
    m_stackTop = 0;
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
#include "h/Compiler.h"
#include "h/Token.h"
#include "h/Chunk.h"

Compiler::Compiler(std::string source) : m_source{std::move(source)}, m_scanner{m_source} {}

const ParseRule& Compiler::getParseRule(TokenType type) {
    return m_parseRules[(size_t)type];
}

Chunk& Compiler::currentChunk() {
    return m_compilingChunk;
}

void Compiler::parsePrecedence(Precedence precedence) {
    advance();
    ParseFn prefixRule = getParseRule(m_previous.type).prefix;
    if (prefixRule == nullptr) {
        error("Expected expression.");
        return;
    }

    (this->*(prefixRule))();

    while (precedence <= getParseRule(m_current.type).precedence) {
        advance();
        ParseFn infixRule = getParseRule(m_previous.type).infix;
        (this->*(infixRule))();
    }
}

void Compiler::expression() {
    parsePrecedence(Precedence::ASSIGNMENT);
}

void Compiler::grouping() {
    expression();
    consume(TokenType::ENDFILE, "Expected ')' after expression.");
}

void Compiler::number() {
    double value = std::stod(m_previous.lexeme);
    emitConstant(Value{value});
}

void Compiler::literal() {
    switch (m_previous.type) {
        case TokenType::TRUE: emitByte(OpCode::TRUE); break;
        case TokenType::FALSE: emitByte(OpCode::FALSE); break;
        case TokenType::NIL: emitByte(OpCode::NIL); break;
        default: break; // Unreachable
    }
}

void Compiler::string() {
    StringObject *object = Allocator::makeStringObject(m_previous.lexeme.substr(1, m_previous.lexeme.size() - 2));
    if (!m_hasAllocated) {
        m_hasAllocated = true;
        m_objects = object;
    }
    emitConstant(Value{object});
}

void Compiler::unary() {
    TokenType operatorType = m_previous.type;

    parsePrecedence(Precedence::UNARY);

    switch (operatorType) {
        case TokenType::BANG: emitByte(OpCode::NOT); break;
        case TokenType::MINUS: emitByte(OpCode::NEGATE); break;
    }
}

void Compiler::binary() {
    TokenType operatorType = m_previous.type;

    const ParseRule &rule = getParseRule(operatorType);
    parsePrecedence(rule.precedence);

    switch (operatorType) {
        case TokenType::EQUAL_EQUAL: emitByte(OpCode::EQUAL); break;
        case TokenType::BANG_EQUAL: emitBytes(OpCode::EQUAL, OpCode::NOT); break;
        case TokenType::LESS: emitByte(OpCode::LESS); break;
        case TokenType::LESS_EQUAL: emitBytes(OpCode::GREATER, OpCode::NOT); break;
        case TokenType::GREATER: emitByte(OpCode::GREATER); break;
        case TokenType::GREATER_EQUAL: emitBytes(OpCode::LESS, OpCode::NOT); break;
        case TokenType::PLUS: emitByte(OpCode::ADD); break;
        case TokenType::MINUS: emitByte(OpCode::SUBTRACT); break;
        case TokenType::STAR: emitByte(OpCode::MULTIPLY); break;
        case TokenType::SLASH: emitByte(OpCode::DIVIDE); break;
    }
}

void Compiler::ternary() {
    parsePrecedence(Precedence::CONDITIONAL);
    consume(TokenType::COLON, "Expected ':' after then value of conditional expression.");
    parsePrecedence(Precedence::ASSIGNMENT);
    emitByte(OpCode::CONDITIONAL);
}

void Compiler::declaration() {
    statement();
}

void Compiler::statement() {
    if (match(TokenType::PRINT)) printStatement();
    else expressionStatement();
}

void Compiler::printStatement() {
    expression();
    emitByte(OpCode::PRINT);
    consume(TokenType::SEMICOLON, "Expected ';' after print statement.");
}

void Compiler::expressionStatement() {
    expression();
    consume(TokenType::SEMICOLON, "Expected ';' after expression.");
}

bool Compiler::compile() {
    advance();
    while (!isAtEnd()) {
        declaration();
    }
    emitByte(OpCode::RETURN);
    return !m_hadError;
}

void Compiler::errorAt(const Token &token, const std::string &message) {
    std::cerr << "[line " << token.line << "] Error";

    if (token.type == TokenType::ENDFILE) {
        std::cerr << " at end: " << message << "\n\n";
    } else {
        if (token.type == TokenType::ERROR) {
            std::cerr << ":\n";
        } else {
            std::cerr << " at '" << token.lexeme << "':\n";
        }

        std::cerr << "    " << m_scanner.getSourceLine(token.line) << "\n";
        for (int i = 1; i < token.col; ++i) {
            std::cerr << " ";
        }
        std::cerr << "    ^\n";
        std::cerr << message << "\n\n";
    }

    m_hadError = true;
    while (m_current.type != TokenType::SEMICOLON) advance();
}

void Compiler::errorAtCurrent(const std::string &message) {
    errorAt(m_current, message);
}

void Compiler::error(const std::string &message) {
    errorAt(m_previous, message);
}

void Compiler::advance() {
    m_previous = m_current;

    while (true) {
        m_current = m_scanner.scanToken();
        if (m_current.type != TokenType::ERROR) break;

        errorAtCurrent(m_current.lexeme);
    }
}

bool Compiler::check(TokenType expected) {
    return m_current.type == expected;
}

bool Compiler::match(TokenType expected) {
    if (check(expected)) {
        advance();
        return true;
    }
    return false;
}

void Compiler::consume(TokenType type, const std::string &message) {
    if (m_current.type == type) {
        advance();
    } else {
        errorAtCurrent(message);
    }
}

bool Compiler::isAtEnd() {
    return m_current.type == TokenType::ENDFILE;
}

void Compiler::emitByte(uint8_t byte) {
    currentChunk().write(byte, m_previous.line);
}

void Compiler::emitBytes(uint8_t byte1, uint8_t byte2) {
    emitByte(byte1);
    emitByte(byte2);
}

void Compiler::emitConstant(Value value) {
    currentChunk().writeConstant(value, m_previous.line);
}

Object *Compiler::objects() {
    return m_objects;
}

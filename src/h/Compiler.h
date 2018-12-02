#ifndef MATILDA_COMPILER_H
#define MATILDA_COMPILER_H

#include <array>
#include <functional>
#include <string>

#include "Allocator.h"
#include "Chunk.h"
#include "Scanner.h"
#include "Token.h"

enum class Precedence {
    NONE,
    ASSIGNMENT,  // =
    CONDITIONAL, // ?:
    OR,          // or
    AND,         // and
    EQUALITY,    // == !=
    COMPARISON,  // < > <= >=
    TERM,        // + -
    FACTOR,      // * /
    UNARY,       // - !
    CALL,        // () []
    PRIMARY,
};

class Compiler;
typedef void (Compiler::*ParseFn)();

struct ParseRule {
    ParseFn prefix;
    ParseFn infix;
    Precedence precedence;
};

class Compiler {
private:
    std::string m_source;
    Chunk m_compilingChunk;
    Scanner m_scanner;

    bool m_hadError = false;
    bool m_panicMode = false;

    Token m_previous;
    Token m_current;

    void advance();
    bool check(TokenType expected);
    bool match(TokenType expected);
    void consume(TokenType type, const std::string &message);
    bool isAtEnd();

    void emitByte(uint8_t byte);
    void emitBytes(uint8_t byte1, uint8_t byte2);
    void emitConstant(Value value);

    void errorAt(const Token &token, const std::string &message);
    void errorAtCurrent(const std::string &message);
    void error(const std::string &message);

    const ParseRule& getParseRule(TokenType type);
    void parsePrecedence(Precedence precedence);

    void expression();

    // Expression parse rules
    void grouping();
    void variable();
    void number();
    void literal();
    void call();
    void string();
    void unary();
    void binary();
    void ternary();

    std::array<ParseRule, 47> m_parseRules = {
            ParseRule{&Compiler::grouping,   &Compiler::call,    Precedence::CALL}, // LEFT_PAREN
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // RIGHT_PAREN
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // LEFT_SQUARE
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // RIGHT_SQUARE
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // COMMA
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // DOT
            ParseRule{&Compiler::unary,      &Compiler::binary,  Precedence::TERM}, // MINUS
            ParseRule{nullptr,               &Compiler::binary,  Precedence::TERM}, // PLUS
            ParseRule{nullptr,               &Compiler::ternary, Precedence::CONDITIONAL}, // QUESTION
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // SEMICOLON
            ParseRule{nullptr,               &Compiler::binary,  Precedence::FACTOR}, // SLASH
            ParseRule{nullptr,               &Compiler::binary,  Precedence::FACTOR}, // STAR
            ParseRule{&Compiler::unary,      nullptr,            Precedence::UNARY}, // BANG
            ParseRule{nullptr,               &Compiler::binary,  Precedence::EQUALITY}, // BANG_EQUAL
            ParseRule{nullptr,               &Compiler::binary,  Precedence::ASSIGNMENT}, // EQUAL
            ParseRule{nullptr,               &Compiler::binary,  Precedence::EQUALITY}, // EQUAL_EQUAL
            ParseRule{nullptr,               &Compiler::binary,  Precedence::COMPARISON}, // GREATER
            ParseRule{nullptr,               &Compiler::binary,  Precedence::COMPARISON}, // GREATER_EQUAL
            ParseRule{nullptr,               &Compiler::binary,  Precedence::COMPARISON}, // LESS
            ParseRule{nullptr,               &Compiler::binary,  Precedence::COMPARISON}, // LESS_EQUAL
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // COLON
            ParseRule{nullptr,               &Compiler::binary,  Precedence::ASSIGNMENT}, // COLON_EQUAL
            ParseRule{nullptr,               &Compiler::binary,  Precedence::ASSIGNMENT}, // COLON_COLON_EQUAL
            ParseRule{&Compiler::variable,   nullptr,            Precedence::NONE}, // IDENTIFIER
            ParseRule{&Compiler::string,     nullptr,            Precedence::NONE}, // STRING
            ParseRule{&Compiler::number,     nullptr,            Precedence::NONE}, // NUMBER
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // AND
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // BOOL
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // CLASS
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // CONST
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // ELSE
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // END
            ParseRule{&Compiler::literal,    nullptr,            Precedence::NONE}, // FALSE
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // FUN
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // FOR
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // IF
            ParseRule{&Compiler::literal,    nullptr,            Precedence::NONE}, // NIL
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // OR
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // RETURN
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // SUPER
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // THIS
            ParseRule{&Compiler::literal,    nullptr,            Precedence::NONE}, // TRUE
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // VAR
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // WHILE
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // ERROR
            ParseRule{nullptr,               nullptr,            Precedence::NONE} // ENDFILE
    };

    void declaration();

    // Declaration types
    //void variableDeclaration();

    void statement();

    // Statement types
    void printStatement();
    void expressionStatement();

public:
    explicit Compiler(std::string source);
    bool compile();
    Chunk& currentChunk();
};



#endif //MATILDA_COMPILER_H

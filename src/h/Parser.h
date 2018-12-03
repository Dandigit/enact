#ifndef ENACT_PARSER_H
#define ENACT_PARSER_H

#include <array>
#include <memory>
#include <string>

#include "Allocator.h"
#include "Chunk.h"
#include "Scanner.h"
#include "Token.h"

#include "../ast/Stmt.h"

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

class Parser;
typedef std::shared_ptr<Expr> (Parser::*PrefixFn)();
typedef std::shared_ptr<Expr> (Parser::*InfixFn)(std::shared_ptr<Expr>);

struct ParseRule {
    PrefixFn prefix;
    InfixFn infix;
    Precedence precedence;
};

class Parser {
private:
    std::string m_source;
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
    std::shared_ptr<Expr> parsePrecedence(Precedence precedence);

    std::shared_ptr<Expr> expression();

    // Prefix parse rules
    std::shared_ptr<Expr> grouping();
    std::shared_ptr<Expr> variable();
    std::shared_ptr<Expr> number();
    std::shared_ptr<Expr> literal();
    std::shared_ptr<Expr> string();
    std::shared_ptr<Expr> unary();

    // Infix parse rules
    std::shared_ptr<Expr> call(std::shared_ptr<Expr> callee);
    std::shared_ptr<Expr> binary(std::shared_ptr<Expr> left);
    std::shared_ptr<Expr> ternary(std::shared_ptr<Expr> condition);

    std::array<ParseRule, 47> m_parseRules = {
            ParseRule{&Parser::grouping,   &Parser::call,    Precedence::CALL}, // LEFT_PAREN
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // RIGHT_PAREN
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // LEFT_SQUARE
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // RIGHT_SQUARE
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // COMMA
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // DOT
            ParseRule{&Parser::unary,      &Parser::binary,  Precedence::TERM}, // MINUS
            ParseRule{nullptr,               &Parser::binary,  Precedence::TERM}, // PLUS
            ParseRule{nullptr,               &Parser::ternary, Precedence::CONDITIONAL}, // QUESTION
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // SEMICOLON
            ParseRule{nullptr,               &Parser::binary,  Precedence::FACTOR}, // SLASH
            ParseRule{nullptr,               &Parser::binary,  Precedence::FACTOR}, // STAR
            ParseRule{&Parser::unary,      nullptr,            Precedence::UNARY}, // BANG
            ParseRule{nullptr,               &Parser::binary,  Precedence::EQUALITY}, // BANG_EQUAL
            ParseRule{nullptr,               &Parser::binary,  Precedence::ASSIGNMENT}, // EQUAL
            ParseRule{nullptr,               &Parser::binary,  Precedence::EQUALITY}, // EQUAL_EQUAL
            ParseRule{nullptr,               &Parser::binary,  Precedence::COMPARISON}, // GREATER
            ParseRule{nullptr,               &Parser::binary,  Precedence::COMPARISON}, // GREATER_EQUAL
            ParseRule{nullptr,               &Parser::binary,  Precedence::COMPARISON}, // LESS
            ParseRule{nullptr,               &Parser::binary,  Precedence::COMPARISON}, // LESS_EQUAL
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // COLON
            ParseRule{nullptr,               &Parser::binary,  Precedence::ASSIGNMENT}, // COLON_EQUAL
            ParseRule{nullptr,               &Parser::binary,  Precedence::ASSIGNMENT}, // COLON_COLON_EQUAL
            ParseRule{&Parser::variable,   nullptr,            Precedence::NONE}, // IDENTIFIER
            ParseRule{&Parser::string,     nullptr,            Precedence::NONE}, // STRING
            ParseRule{&Parser::number,     nullptr,            Precedence::NONE}, // NUMBER
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // AND
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // BOOL
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // CLASS
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // CONST
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // ELSE
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // END
            ParseRule{&Parser::literal,    nullptr,            Precedence::NONE}, // FALSE
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // FUN
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // FOR
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // IF
            ParseRule{&Parser::literal,    nullptr,            Precedence::NONE}, // NIL
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // OR
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // RETURN
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // SUPER
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // THIS
            ParseRule{&Parser::literal,    nullptr,            Precedence::NONE}, // TRUE
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // VAR
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // WHILE
            ParseRule{nullptr,               nullptr,            Precedence::NONE}, // ERROR
            ParseRule{nullptr,               nullptr,            Precedence::NONE} // ENDFILE
    };

    std::shared_ptr<Stmt> declaration();

    // Declaration types
    std::shared_ptr<Stmt> variableDeclaration(bool isConst);

    std::shared_ptr<Stmt> statement();

    // Statement types
    std::shared_ptr<Stmt> printStatement();
    std::shared_ptr<Stmt> expressionStatement();

public:
    explicit Parser(std::string source);
    std::vector<std::shared_ptr<Stmt>> parse();
    bool hadError();
};



#endif //ENACT_COMPILER_H

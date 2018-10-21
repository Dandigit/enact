#ifndef MATILDA_TOKEN_H
#define MATILDA_TOKEN_H

#include <string>

#include "TokenType.h"

class Token {
    TokenType m_type;
    std::string m_lexeme;
    uint32_t m_line;
    std::string m_literal;

public:
    Token(TokenType type, std::string lexeme, uint32_t line, std::string literal);

    TokenType type() const;
    std::string lexeme() const;
    uint32_t line() const;
    std::string literal() const;

    std::string toString() const;
};

#endif //MATILDA_TOKEN_H

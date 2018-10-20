#ifndef MATILDA_TOKEN_H
#define MATILDA_TOKEN_H

#include <string>

#include "TokenType.h"

using std::string;

class Token {
    TokenType m_type;
    string m_lexeme;
    uint32_t m_line;

public:
    Token(TokenType type, string lexeme, uint32_t line);

    TokenType type() const;
    string lexeme() const;
    uint32_t line() const;

    string toString() const;
};

#endif //MATILDA_TOKEN_H

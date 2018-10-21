#ifndef MATILDA_TOKEN_H
#define MATILDA_TOKEN_H

#include <string>

#include "TokenType.h"
#include "Object.h"

using std::string;

class Token : public Object {
    TokenType m_type;
    string m_lexeme;
    uint32_t m_line;
    Object m_literal;

public:
    Token(TokenType type, string lexeme, uint32_t line, Object literal);

    TokenType type() const;
    string lexeme() const;
    uint32_t line() const;
    Object literal() const;

    string toString() const;
};

#endif //MATILDA_TOKEN_H

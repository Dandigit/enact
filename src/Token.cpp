#include "../h/Token.h"

Token::Token(TokenType type, string lexeme, uint32_t line, Object literal) :
    m_type{ type }, m_lexeme{ lexeme }, m_line{ line }, m_literal{ literal } {}

TokenType Token::type() const { return m_type; }
string Token::lexeme() const { return m_lexeme; }
uint32_t Token::line() const { return m_line; }
Object Token::literal() const { return m_literal; };

string Token::toString() const {
    return "token: (\ntype: " + m_type +
        "\nlexeme: " + m_lexeme +
        "\nline: " + std::to_string(m_line);
}
#include "../h/Token.h"

Token::Token(TokenType type, std::string lexeme, uint32_t line, std::string literal) :
    m_type{ type }, m_lexeme{ lexeme }, m_line{ line }, m_literal{ literal } {}

TokenType Token::type() const { return m_type; }
std::string Token::lexeme() const { return m_lexeme; }
uint32_t Token::line() const { return m_line; }
std::string Token::literal() const { return m_literal; };

std::string Token::toString() const {
    return "type: " + ::toString(m_type) +
        "\nlexeme: " + m_lexeme +
        "\nline: " + std::to_string(m_line) +
        "\nliteral: " + m_literal + "\n";
}
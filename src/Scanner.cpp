#include "../h/Scanner.h"

Scanner::Scanner(std::string source) :
    m_source { source } {}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        // We're at the beginning of the next lexeme
        m_start = m_current;
        scanToken();
    }

    m_tokens.push_back(Token{ ENDFILE, "", m_line, "" });
    return m_tokens;
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        // Single character tokens
        case '(': addToken(LEFT_PAREN); ++m_openParen; break;
        case ')': addToken(RIGHT_PAREN); --m_openParen; break;
        case '[': addToken(LEFT_SQUARE); ++m_openParen; break;
        case ']': addToken(RIGHT_SQUARE); --m_openParen; break;
        case ':': addToken(COLON); break;
        case ',': addToken(COMMA); break;
        case '.': addToken(DOT); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case ';': addToken(SEMICOLON); break;
        case '*': addToken(STAR); break;
        case '?': addToken(QUESTION); break;

        // One or two characters
        case '!': addToken(match('=') ? BANG_EQUAL : BANG); break;
        case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;
        case '<': addToken(match('=') ? LESS_EQUAL : LESS); break;
        case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;

        // Handle comments or slash
        case '/':
            // Single line comment
            if (match('/')) {
                while (peek() != '\n' && !isAtEnd()) advance();
            // Block comment
            } else if (match('*')) {
                blockComment();
            // Plain ol' slash
            } else {
                addToken(SLASH);
            }
            break;

        // Ignore whitespace
        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            ++m_line;
            optionalSemicolon();
            break;

        case '"': string(); break;

        // Not allowed
        default:
            if (isDigit(c)) {
                number();
            } else {
                std::string errorMessage {"Unexpected character '"};
                errorMessage += c;
                errorMessage += "'.";
                Matilda::error(m_line, errorMessage);
                break;
            }
    }
}

void Scanner::optionalSemicolon() {

}

void Scanner::blockComment() {

}

void Scanner::identifier() {

}

void Scanner::number() {
    while (isDigit(peek())) advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        // Eat the '.'
        advance();

        while (isDigit(peek())) advance();
    }

    addToken(NUMBER,
            m_source.substr(m_start, m_current));
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') ++m_line;
        advance();
    }

    // Unterminated string.
    if (isAtEnd()) {
        Matilda::error(m_line, "Unterminated string.");
        return;
    }

    // Close quote.
    advance();

    // Trim the quotes
    std::string value {m_source.substr(m_start + 1, m_current - 1)};
    addToken(STRING, value);
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (m_source.at(m_current) != expected) return false;

    ++m_current;
    return true;
}

char Scanner::peek() const {
    if (isAtEnd()) return '\0';
    return m_source.at(m_current);
}

char Scanner::peekNext() const {
    if (m_current + 1 >= m_source.length()) return '\0';
    return m_source.at(m_current + 1);
}

bool Scanner::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

bool Scanner::isAtEnd() const {
    return m_current >= m_source.length();
}

char Scanner::advance() {
    return m_source.at(m_current++);
}

void Scanner::addToken(TokenType type) {
    addToken(type, "");
}

void Scanner::addToken(TokenType type, std::string literal) {
    std::string lexeme = m_source.substr(m_start, m_current);
    m_tokens.push_back(Token{type, lexeme, m_line, literal});
}
#include "../h/Scanner.h"

Scanner::Scanner(string source) :
    m_source { source } {}

vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        // We're at the beginning of the next lexeme
        start = current;
        scanToken();
    }

    m_tokens.push_back(Token{ ENDFILE, "", line })
}
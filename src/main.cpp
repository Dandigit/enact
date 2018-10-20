#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::ifstream;
using std::string;
using std::vector;

enum class ExitCode {
    INVALID_ARGUMENTS = 65,
    FILE_ERROR = 70,
    STATIC_ERROR = 75,
};

namespace Matilda {
    bool hadError {false};

    void run(string source) {
        Scanner scanner{source};
        vector<Token> tokens = scanner.scanTokens();

        // Temporary: just print tokens
        for (const Token token : tokens) {
            token.print();
        }
    }

    void runFile(string path) {
        // Get the file contents.
        ifstream file{path};

        // Check that the file opened successfully
        if (!file.is_open()) {
            std::cerr << "Error: Unable to read file '" + path + "'.";
            std::exit((int) ExitCode::FILE_ERROR);
        }

        string fileContents{""};
        string currentLine{""};

        while (std::getline(std::cin, currentLine)) {
            fileContents += currentLine;
        }

        run(fileContents);

        if (hadError) std::exit((int)ExitCode::STATIC_ERROR);
    }

    void runPrompt() {
        while (true) {
            std::cout << "matilda > ";

            string input{""};
            std::getline(std::cin, input);

            run(input + "\n");
            hadError = false;
        }
    }

    void report(uint32_t line, string where, string message) {
        std::cerr << "[line " << line << "] Error " << where << ": " << message << "\n";
        hadError = true;
    }

    void error(uint32_t line, string message) {
        report(line, "", message);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        // Too many arguments.
        std::cerr << "Usage: matilda [file]\n";
        std::exit((int)ExitCode::INVALID_ARGUMENTS);
    } else if (argc == 2) {
        // Run the provided file.
        Matilda::runFile(argv[1]);
    } else {
        // No arguments, initialize REPL.
        Matilda::runPrompt();
    }

    return 0;
}
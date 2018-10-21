#include "../h/Matilda.h"

bool Matilda::hadError {false};

void Matilda::report(uint32_t line, std::string where, std::string message) {
    std::cerr << "[line " << line << "] Error " << where << ": " << message << "\n";
    hadError = true;
}

void Matilda::run(std::string source) {
    Scanner scanner{source};
    std::vector<Token> tokens = scanner.scanTokens();

    // Temporary: just print tokens
    for (const Token token : tokens) {
        std::cout << token.toString() << "\n";
    }
}

void Matilda::runFile(std::string path) {
    // Get the file contents.
    std::ifstream file{path};

    // Check that the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Unable to read file '" + path + "'.";
        std::exit((int) ExitCode::FILE_ERROR);
    }

    std::string fileContents{""};
    std::string currentLine{""};

    while (std::getline(std::cin, currentLine)) {
        fileContents += currentLine;
    }

    run(fileContents);

    if (hadError) std::exit((int)ExitCode::STATIC_ERROR);
}

void Matilda::runPrompt() {
    while (true) {
        std::cout << "matilda > ";

        std::string input{""};
        std::getline(std::cin, input);

        run(input + "\n");
        hadError = false;
    }
}

void Matilda::error(uint32_t line, std::string message) {
    report(line, "", message);
}

void Matilda::start(int argc, char *argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: matilda [file]\n";
        std::exit((int)ExitCode::INVALID_ARGUMENTS);
    } else if (argc == 2) {
        // Run the provided file.
        runFile(argv[1]);
    } else {
        // No arguments, initialize REPL.
        runPrompt();
    }
}

int main(int argc, char *argv[]) {
    Matilda::start(argc, argv);

    return 0;
}
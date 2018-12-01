#include <csignal>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "h/Chunk.h"
#include "h/Compiler.h"
#include "h/Matilda.h"
#include "h/VM.h"

VM Matilda::m_vm{};

InterpretResult Matilda::run(const std::string &source) {
    Compiler compiler{source};
    if (!compiler.compile()) return InterpretResult::COMPILE_ERROR;
    std::cout << compiler.currentChunk().disassemble();

    return m_vm.run(compiler.currentChunk());
}

void Matilda::runFile(const std::string &path) {
    // Get the file contents.
    std::ifstream file{path};

    // Check that the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Unable to read file '" + path + "'.";
        std::exit((int)ExitCode::FILE_ERROR);
    }

    std::string fileContents;
    std::string currentLine;

    while (std::getline(std::cin, currentLine)) {
        fileContents += currentLine;
    }

    InterpretResult result = run(fileContents);

    if (result == InterpretResult::COMPILE_ERROR) exit((int)ExitCode::COMPILE_ERROR);
    if (result == InterpretResult::RUNTIME_ERROR) exit((int)ExitCode::RUNTIME_ERROR);
}

void Matilda::runPrompt() {
    while (true) {
        std::cout << "matilda > ";

        std::string input;
        std::getline(std::cin, input);

        run(input + "\n");
    }
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
    Allocator::freeAll();

    return 0;
}
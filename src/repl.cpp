#include<iostream>
#include "repl.h"

namespace bigNumCalculator {
namespace repl {

const char REPL_CHAR = '>';
const std::string QUIT_CHAR = "q";
const std::string QUIT_CMD = ".quit";
const std::string HELP_CMD = ".help";

void startup_message() {
    std::cout << "BigNumCalculator by DSkrzypiec. Type .help for help." << std::endl;
}

void run_repl() {
    std::string line;

    for (;;) {
        std::cout << REPL_CHAR;
        std::getline(std::cin, line);

        if (line == QUIT_CHAR || line == QUIT_CMD) {
            break;
        }

        if (line == HELP_CMD) {
            show_help();
        }

        // parse
        // eval
        // print
        std::cout << "Your words: " << line << std::endl; // TODO
    }
}

void show_help() {
    // TODO
    std::cout << "TODO: Make help docs" << std::endl;
}

} // repl namespace
} // bigNumCalculator namespace

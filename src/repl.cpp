#include <iostream>
#include <memory>
#include <vector>
#include "repl.h"
#include "Scanner.h"
#include "Parser.h"

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
    std::vector<std::unique_ptr<Word>> words;

    for (;;) {
        std::cout << REPL_CHAR;
        std::getline(std::cin, line);

        if (line == QUIT_CHAR || line == QUIT_CMD) {
            break;
        }

        if (line == HELP_CMD) {
            show_help();
            continue;
        }

        // TODO: Temp hack for fast testing
        // This part will be placed inside the parser
        Scanner scanner(line);
        words.clear();

        for (;;) {
            auto word = scanner.scan();
            auto token_str = TokenStrings[word.token];

            if (word.token != Token::END) {
                words.push_back(std::make_unique<Word>(word));
            }

            if (word.token == Token::END) {
                std::cout << "Words before parsing: [";
                for (auto& w : words) {
                    std::cout << TokenStrings[w->token] << " ";
                }; std::cout << "]" << std::endl;

                Parser parser;
                auto tree = parser.parse(words);

                if (tree.error != nullptr) {
                    std::cout << "[Error] " << tree.error->message << std::endl;
                    words.clear();
                }

                tree.result->print();
                break;
            }

            if (word.token == Token::ILLEGAL) {
                std::cout << "ILLEGAL!: " << word.word[0] << std::endl;
                break;
            }
        }
    }
}

void show_help() {
    // TODO
    std::cout << "TODO: Make help docs" << std::endl;
}

} // repl namespace
} // bigNumCalculator namespace

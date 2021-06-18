#include "Parser.h"

#include <algorithm>
#include <memory>
#include <vector>
#include <iostream>

#include "tokens.h"

namespace bigNumCalculator {

void Parser::grow_tree(std::unique_ptr<Word>& word, Token op_token) {
    if (_root == nullptr) {
        _root = std::make_shared<AST>(word, op_token);
        _current_ast = _root;
        _previous_op = op_token;
        return;
    }

    if (TokenPrecedenceMap.find(op_token) == TokenPrecedenceMap.end()) {
        std::cout << "There is no precedence for current token ["
            << TokenStrings[op_token] << "]" << std::endl;
        return;
    }

    if (TokenPrecedenceMap.find(_previous_op) == TokenPrecedenceMap.end()) {
        std::cout << "There is no precedence for previous token ["
            << TokenStrings[_previous_op] << "]" << std::endl;
        return;
    }

    int current_op_precedence = TokenPrecedenceMap.at(op_token);
    int previous_op_precedence = TokenPrecedenceMap.at(_previous_op);

    if (current_op_precedence <= previous_op_precedence) {
        _current_ast->rightChild = std::make_shared<AST>(word, op_token);
        _current_ast = _current_ast->rightChild;
        _previous_op = op_token;

        return;
    }

    // Move root as left child and update root
    auto new_root = std::make_shared<AST>(_root, word, op_token);
    _root = new_root;
    _current_ast = new_root;
    _previous_op = op_token;
}

// Main parse method.
ParsingResult Parser::parse(std::vector<std::unique_ptr<Word>>& words) {
    if (words.size() < 3) {
        auto error = std::make_shared<ParsingError>(
            1, "Expression should have at least one operation");
        return ParsingResult{nullptr, error};
    }

    for (auto id = 0; id < (int)words.size(); id += 2) {
        if (id == (int)words.size() - 1) {
            // Add completing number to unfinished operation
            _current_ast->rightNumber = std::move(words[id]);
            break;
        }

        if (!token_is_literal(words[id]->token)) {
            auto error = std::make_shared<ParsingError>(
                id, "Invalid sequence of tokens. Expected number before the "
                    "operation");
            return ParsingResult{nullptr, error};
        }

        if (words[id + 1]->token != Token::END && !token_is_operator(words[id + 1]->token)) {
            auto error = std::make_shared<ParsingError>(
                id,
                "Invalid sequence of tokens. Expected operation after number");
            return ParsingResult{nullptr, error};
        }

        grow_tree(words[id], words[id + 1]->token);
    }

    // TODO: Handle parenthesis later

    return ParsingResult{_root, nullptr};
}

void print_word_with_spaces(std::unique_ptr<Word>& word, int indent) {
    for (int i = 0; i < indent; i++) {
        std::cout << " ";
    }

    for (const auto& c : word->word) {
        std::cout << c;
    }

    std::cout << std::endl;
}

void print_token_with_spaces(Token token, int indent) {
    for (int i = 0; i < indent; i++) {
        std::cout << " ";
    }

    std::cout << TokenStrings[token] << std::endl;
}


// TODO: Make a ASCII visualization
void AST::print(int indent) {
    const int offset = 4;

    print_token_with_spaces(opToken, indent);

    if (leftNumber != nullptr) {
        print_word_with_spaces(leftNumber, indent + offset);
    }

    if (rightNumber != nullptr) {
        print_word_with_spaces(rightNumber, indent + offset);
    }

    if (leftChild != nullptr) {
        leftChild->print(indent + offset);
    }

    if (rightChild != nullptr) {
        rightChild->print(indent + offset);
    }
}


} // bigNumCalculator

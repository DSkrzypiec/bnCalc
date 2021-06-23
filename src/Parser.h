#ifndef PARSER_H_
#define PARSER_H_

#include<string>
#include<memory>

#include "Scanner.h"

namespace bigNumCalculator {

// Abstract Syntax Tree for expression to be calculated.
//
//          +
//         / \
//        /   \
//  (INT, 15) (INT, 42)
//
struct AST {
    Token opToken;
    std::unique_ptr<Word> leftNumber;
    std::unique_ptr<Word> rightNumber;
    std::shared_ptr<AST> leftChild;
    std::shared_ptr<AST> rightChild;

    AST() {}

    AST(Token op_token)
        : opToken(op_token), leftNumber(nullptr), rightNumber(nullptr),
          leftChild(nullptr), rightChild(nullptr) {}

    AST(std::unique_ptr<Word>& word, Token op_token)
        : opToken(op_token), leftNumber(std::move(word)), rightNumber(nullptr),
          leftChild(nullptr), rightChild(nullptr) {}

    AST(std::shared_ptr<AST>& left_child, std::unique_ptr<Word>& word,
        Token op_token)
        : opToken(op_token), leftNumber(nullptr), rightNumber(std::move(word)),
          leftChild(left_child), rightChild(nullptr) {}

    void print(int indent = 0);
};

// TODO
struct ParsingError {
    int position;
    std::string message;

    ParsingError(int pos, std::string msg) : position(pos), message(msg) {}
};

struct ParsingResult {
    std::shared_ptr<AST> result;
    std::shared_ptr<ParsingError> error;
};

// Parser parses AST based on given Words.
class Parser {
private:
    std::shared_ptr<AST> _root = nullptr;
    std::shared_ptr<AST> _current_ast = nullptr;
    Token _previous_op;
    int _current_token_id;

    void grow_tree(std::unique_ptr<Word>& word, Token op_token);
public:
    ParsingResult parse(std::vector<std::unique_ptr<Word>>& words);
};

} // bigNumCalculator namespace

#endif // PARSER_H_

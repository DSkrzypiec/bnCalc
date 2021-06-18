#ifndef TOKENS_H_
#define TOKENS_H_

#include <vector>
#include <unordered_map>
#include <string>

namespace bigNumCalculator {

enum Token {
    COMMENT,
    ILLEGAL,
    END,

    _literalsBegin,
    INT,
    REAL,
    _literalsEnd,

    _operatorsBegin,
    ADD,        // +
    SUB,        // -
    MUL,        // *
    DIV,        // /
    MOD,        // %
    LPARENT,    // (
    RPARENT,    // )
    POWER,      // ^
    _operatorsEnd,

    PERIOD      // .
};

bool token_is_literal(const Token token);
bool token_is_operator(const Token token);
bool token_is_illegal(const Token token);
bool token_is_end(const Token token);

static const std::unordered_map<Token, int> TokenPrecedenceMap = {
    {Token::LPARENT, 1},
    {Token::RPARENT, 1},
    {Token::POWER, 2},
    {Token::MUL, 3},
    {Token::DIV, 3},
    {Token::MOD, 3},
    {Token::ADD, 4},
    {Token::SUB, 4}
};

static const std::vector<std::string> TokenStrings = {
    "COMMENT",
    "ILLEGAL",
    "END",
    "_literalsBegin",
    "INT",
    "REAL",
    "_literalsEnd",
    "_operatorsBegin",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "MOD",
    "LPARENT",
    "RPARENT",
    "POWER",
    "_operatorsBegin",
    "PERIOD"
};

} // bigNumCalculator namespace

#endif // TOKENS_H_

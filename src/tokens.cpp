#include "tokens.h"

namespace bigNumCalculator {

bool token_is_literal(const Token token) {
    return token > Token::_literalsBegin && token < Token::_literalsEnd;
}

bool token_is_operator(const Token token) {
    return token > Token::_operatorsBegin && token < Token::_operatorsEnd;
}

bool token_is_illegal(const Token token) {
    return token == Token::ILLEGAL;
}

bool token_is_end(const Token token) { return token == Token::END; }

} // bigNumCalculator namespace


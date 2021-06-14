#include <iostream>
#include <cctype>
#include "Scanner.h"

namespace bigNumCalculator {

Scanner::Scanner(const std::string& content)
   : _source(content.begin(), content.end()),
     _source_size{(int)content.size()}
{
    if (content.size() == 0) {
        return;
    }

    _current = _source[0];
    _offset = 0;
}

Word Scanner::scan() {
    skip_whitespace();

    switch (_current) {
        case EOFCHAR:
            return Word{Token::END, std::vector<char> { }};
        case '+':
            next();
            return Word{Token::ADD, std::vector<char> { '+' }};
        case '*':
            next();
            return Word{Token::MUL, std::vector<char> { '*' }};
        case '-':
            next();
            return Word{Token::SUB, std::vector<char> { '-' }};
        case '/':
            next();
            return Word{Token::DIV, std::vector<char> { '/' }};
        case '%':
            next();
            return Word{Token::MOD, std::vector<char> { '%' }};
        case '(':
            next();
            return Word{Token::LPARENT, std::vector<char> { '(' }};
        case ')':
            next();
            return Word{Token::RPARENT, std::vector<char> { ')' }};
        case '^':
            next();
            return Word{Token::POWER, std::vector<char> { '^' }};
    }

    if (std::isdigit(_current)) {
        return scan_number();
    }

    return Word{Token::ILLEGAL, std::vector<char> { _current }};
}

// scan_number scans numbers - integers and real numbers. Real number can be
// expressed in decimal or scientific notation.
Word Scanner::scan_number() {
    auto start_position = _offset;
    auto prev_char = _current;
    auto token = Token::INT;

    for (;;) {
        next();

        if (!std::isdigit(_current) && _current != '.' && _current != 'e'
                && _current != 'E' && _current != '+' && _current != '-') {
            break;
        }

        if (_current == '.') {
            token = Token::REAL;
        }

        if ((_current == '+' || _current == '-') && (prev_char != 'e' || prev_char != 'E')) {
            break;
        }

        prev_char = _current;
    }

    auto start = _source.begin() + start_position;
    auto end = _source.begin() + _offset;
    std::vector<char> number(start, end);

    return Word{token, number};
}

void Scanner::next() {
    if (_offset + 1 >= (int)_source.size()) {
        _offset = _source_size;
        _current = EOFCHAR;
        return;
    }

    _offset++;
    _current = _source[_offset];
}

void Scanner::skip_whitespace() {
    while (std::isspace(_source[_offset])) {
        next();
    }
}

} // bigNumCalculator namespace

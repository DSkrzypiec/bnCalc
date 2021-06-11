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
    }

    if (std::isdigit(_current)) {
        auto number = scan_number();
        return Word{Token::INT, number};
    }

    return Word{Token::ILLEGAL, std::vector<char> { _current }};
}

std::vector<char> Scanner::scan_number() {
    // TODO: Only integeres are handeled now
    auto start_position = _offset;

    for (;;) {
        next();

        if (!std::isdigit(_current)) {
            break;
        }
    }

    auto start = _source.begin() + start_position;
    auto end = _source.begin() + _offset;
    std::vector<char> number(start, end);

    return number;
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

char Scanner::peek() {
    if (_offset + 1 < _source_size) {
        return _source[_offset + 1];
    }

    return 0;
}

void Scanner::skip_whitespace() {
    while (std::isspace(_source[_offset])) {
        next();
    }
}

} // bigNumCalculator namespace

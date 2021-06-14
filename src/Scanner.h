#include <string>
#include <vector>
#include "tokens.h"

namespace  bigNumCalculator {

static const char EOFCHAR = -1;

// Represents scanned word as pair of itself and token it represents.
struct Word {
    Token token;
    std::vector<char> word;
};

// Scanner scans one token at the time.
class Scanner {
private:
    std::vector<char> _source;
    int _source_size;
    char _current = EOFCHAR;
    int _offset = 0;

    void next();
    void skip_whitespace();
    Word scan_number();

public:
    Scanner(const std::string& content);
    Word scan();
};

} // bigNumCalculator namespace

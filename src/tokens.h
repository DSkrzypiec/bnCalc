#include <vector>
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
    PERIOD,     // .
    POWER,      // ^
    _operatorsEnd
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
    "PERIOD",
    "POWER",
    "_operatorsBegin"
};

} // bigNumCalculator namespace

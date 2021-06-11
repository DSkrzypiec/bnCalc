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

} // bigNumCalculator namespace

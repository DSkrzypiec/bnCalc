#include<iostream>
#include <string>
#include "BigInt.h"
#include "repl.h"

int main() {
    bigNumCalculator::repl::startup_message();
    bigNumCalculator::repl::run_repl();
}

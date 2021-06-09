#include "BigInt.h"
#include <vector>

namespace bigNumCalculator {

BigInt::BigInt(const std::string& num_str) {
    auto index = 0;

    for (const auto& ch : num_str) {
        if (ch >= '0' && ch <= '9') {
            _digits.push_back(ch);
            _num_of_digits++;
            index++;
        }
    }
}

BigInt::BigInt(const std::vector<char>& digits) {
    _num_of_digits = digits.size();
    _digits.reserve(_num_of_digits);

    for (const auto& d : digits) {
        _digits.push_back(d);
    }
}

void BigInt::print() {
    for (auto i = 0; i < _num_of_digits; i++) {
        std::cout << _digits[i];
    }
    std::cout << std::endl;
}

} // bigNumCalculator namespace

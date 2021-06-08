#include<iostream>
#include "BigInt.h"

int main() {
    std::cout << "BigNumCalculator by DSkrzypiec" << std::endl;
    std::cout << "Pass a number..." << std::endl;

    std::string input;
    std::cin >> input;

    bigNumCalculator::BigInt<128> x(input);
    x.print();

    return 0;
}

#ifndef BIG_INT_H_
#define BIG_INT_H_

#include<iostream>
#include<string>
#include<vector>

namespace bigNumCalculator {

class BigInt
{
private:
    std::vector<char> _digits;
    int _num_of_digits = 0;

public:
    BigInt(const std::string& num_str);
    BigInt(const std::vector<char>& digits);

    void print();
};
} // bigNumCalculator namespace

#endif // BIG_INT_H_

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

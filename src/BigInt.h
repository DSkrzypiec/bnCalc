#include<iostream>
#include<string>

namespace bigNumCalculator
{

template<int N>
class BigInt
{
private:
    unsigned char _digits[N];
    unsigned char _num_of_digits = 0;

public:
    BigInt(const std::string& num_str);

    void print();
};

template<int N>
BigInt<N>::BigInt(const std::string& num_str) {
    auto index = 0;

    for (const auto& ch : num_str) {
        if (ch >= '0' && ch <= '9') {
            if (index >= N) {
                // TODO
                std::cout << "Digits overflow on " << N << " digits" << std::endl;
            }

            _digits[index] = ch;
            _num_of_digits++;
            index++;
        }
    }
}

template<int N>
void BigInt<N>::print() {
    for (auto i = 0; i < _num_of_digits; i++) {
        std::cout << _digits[i];
    }
    std::cout << std::endl;
}

} // bigNumCalculator namespace

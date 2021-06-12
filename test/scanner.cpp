#include "gtest/gtest.h"
#include "../src/Scanner.h"

using namespace bigNumCalculator;

TEST(scan_number, small_int) {
    Scanner s1("42");
    auto number_word = s1.scan();
    std::vector<char> expected = { '4', '2' };

    EXPECT_EQ(number_word.token, Token::INT);
    EXPECT_EQ(number_word.word, expected);
}

TEST(scan_number, big_int) {
    std::string big_int("421230912093901203912390102390120930129301923123");
    Scanner s1(big_int);
    auto number_word = s1.scan();
    std::vector<char> expected(big_int.begin(), big_int.end());

    EXPECT_EQ(number_word.token, Token::INT);
    EXPECT_EQ(number_word.word, expected);
}

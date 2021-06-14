#include "gtest/gtest.h"
#include <vector>
#include "../src/Scanner.h"

using namespace bigNumCalculator;

TEST(scan_number, small_int) {
    Scanner s("42");
    auto number_word = s.scan();
    std::vector<char> expected = { '4', '2' };

    EXPECT_EQ(number_word.token, Token::INT);
    EXPECT_EQ(number_word.word, expected);
}

TEST(scan_number, small_real) {
    Scanner s("42.675");
    auto number_word = s.scan();
    std::vector<char> expected = { '4', '2', '.', '6', '7', '5' };

    EXPECT_EQ(number_word.token, Token::REAL);
    EXPECT_EQ(number_word.word, expected);
}

TEST(scan_number, small_int_sci) {
    Scanner s("2e9");
    auto number_word = s.scan();
    std::vector<char> expected = { '2', 'e', '9' };

    EXPECT_EQ(number_word.token, Token::INT);
    EXPECT_EQ(number_word.word, expected);
}

TEST(scan_number, small_real_sci) {
    Scanner s("2.18e7");
    auto number_word = s.scan();
    std::vector<char> expected = { '2', '.', '1', '8', 'e', '7' };

    EXPECT_EQ(number_word.token, Token::REAL);
    EXPECT_EQ(number_word.word, expected);
}

TEST(scan_number, big_int) {
    std::string big_int("421230912093901203912390102390120930129301923123");
    Scanner s(big_int);
    auto number_word = s.scan();
    std::vector<char> expected(big_int.begin(), big_int.end());

    EXPECT_EQ(number_word.token, Token::INT);
    EXPECT_EQ(number_word.word, expected);
}

TEST(scan_number, big_real) {
    std::string big_real("2139192391283912831293.9812391929392999319293912939192391923919391923128381283");
    Scanner s(big_real);
    auto number_word = s.scan();
    std::vector<char> expected(big_real.begin(), big_real.end());

    EXPECT_EQ(number_word.token, Token::REAL);
    EXPECT_EQ(number_word.word, expected);
}

TEST(scan_number, sci_notation) {
    std::string number("1.9955e123");
    Scanner s(number);
    auto number_word = s.scan();
    std::vector<char> expected = { '1', '.', '9', '9', '5', '5', 'e', '1', '2', '3' };

    EXPECT_EQ(number_word.token, Token::REAL);
    EXPECT_EQ(number_word.word, expected);
}


TEST(scan_number, sci_notation_capital) {
    std::string number("1.9955E123");
    Scanner s(number);
    auto number_word = s.scan();
    std::vector<char> expected = { '1', '.', '9', '9', '5', '5', 'E', '1', '2', '3' };

    EXPECT_EQ(number_word.token, Token::REAL);
    EXPECT_EQ(number_word.word, expected);
}

TEST(scan_number_op_number, basic) {
    Scanner s("42 + 7");
    std::vector<Word> words = { s.scan(), s.scan(), s.scan() };

    std::vector<char> exp1 = { '4', '2' };
    std::vector<char> exp2 = { '+' };
    std::vector<char> exp3 = { '7' };
    std::vector<std::vector<char>> exps = { exp1, exp2, exp3 };

    std::vector<Token> expTokens = { Token::INT, Token::ADD, Token::INT };

    for (auto i = 0; i < 3; i++) {
        EXPECT_EQ(words[i].token, expTokens[i]);
        EXPECT_EQ(words[i].word, exps[i]);
    }
}

TEST(scan_number_op_number, basic_without_whitespace) {
    Scanner s("42+7");
    std::vector<Word> words = { s.scan(), s.scan(), s.scan() };

    std::vector<char> exp1 = { '4', '2' };
    std::vector<char> exp2 = { '+' };
    std::vector<char> exp3 = { '7' };
    std::vector<std::vector<char>> exps = { exp1, exp2, exp3 };

    std::vector<Token> expTokens = { Token::INT, Token::ADD, Token::INT };

    for (auto i = 0; i < 3; i++) {
        EXPECT_EQ(words[i].token, expTokens[i]);
        EXPECT_EQ(words[i].word, exps[i]);
    }
}

TEST(complex_expression, basic) {
    Scanner s("(42    + 7)* 0.2 ^ 3.5e10");
    std::vector<Word> words;

    for (auto i = 0; i < 100; i++) {
        auto word = s.scan();

        if (word.token == Token::END) {
            break;
        }

        words.push_back(word);
    }

    std::vector<Token> expTokens = {
        Token::LPARENT, Token::INT, Token::ADD, Token::INT,
        Token::RPARENT, Token::MUL, Token::REAL, Token::POWER,
        Token::REAL
    };

    EXPECT_EQ(words.size(), expTokens.size());

    for (int i = 0; i < (int)expTokens.size(); i++) {
        EXPECT_EQ(expTokens[i], words[i].token);
    }
}

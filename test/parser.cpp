#include "../src/Parser.h"
#include "gtest/gtest.h"
#include <memory>
#include <vector>

using namespace bigNumCalculator;

std::string vector_char_to_string(std::vector<char>& chars) {
    return std::string(chars.begin(), chars.end());
}

//      +
//     / \
//    42  7
//
// 42 + 7
TEST(parse_single_op, add) {
    // Arrange
    std::vector<std::unique_ptr<Word>> words;
    auto num1 = std::make_unique<Word>(Token::INT, std::vector<char> { '4' , '2' });
    auto add = std::make_unique<Word>(Token::ADD, std::vector<char> {});
    auto num2 = std::make_unique<Word>(Token::INT, std::vector<char> { '7' });

    words.push_back(std::move(num1));
    words.push_back(std::move(add));
    words.push_back(std::move(num2));

    // Act
    Parser parser;
    auto ast = parser.parse(words);

    // Assert
    EXPECT_FALSE(ast.error);
    EXPECT_EQ(ast.result->opToken, Token::ADD);
    EXPECT_EQ(ast.result->rightNumber->token, Token::INT);
    EXPECT_EQ(ast.result->leftNumber->token, Token::INT);

    EXPECT_EQ(vector_char_to_string(ast.result->leftNumber->word), "42");
    EXPECT_EQ(vector_char_to_string(ast.result->rightNumber->word), "7");
}

//      *
//     / \
//    42  7
//
// 42 * 7
TEST(parse_single_op, mul) {
    // Arrange
    std::vector<std::unique_ptr<Word>> words;
    auto num1 = std::make_unique<Word>(Token::INT, std::vector<char> { '4' , '2' });
    auto mul = std::make_unique<Word>(Token::MUL, std::vector<char> {});
    auto num2 = std::make_unique<Word>(Token::INT, std::vector<char> { '7' });

    words.push_back(std::move(num1));
    words.push_back(std::move(mul));
    words.push_back(std::move(num2));

    // Act
    Parser parser;
    auto ast = parser.parse(words);

    // Assert
    EXPECT_FALSE(ast.error);
    EXPECT_EQ(ast.result->opToken, Token::MUL);
    EXPECT_EQ(ast.result->rightNumber->token, Token::INT);
    EXPECT_EQ(ast.result->leftNumber->token, Token::INT);

    EXPECT_EQ(vector_char_to_string(ast.result->leftNumber->word), "42");
    EXPECT_EQ(vector_char_to_string(ast.result->rightNumber->word), "7");
}

//      +
//     / \
//    42  *
//       / \
//      11  5
//
// 42 + 11 * 5
TEST(parse_two_op, add_mul) {
    // Arrange
    std::vector<std::unique_ptr<Word>> words;
    auto num1 = std::make_unique<Word>(Token::INT, std::vector<char> { '4' , '2' });
    auto add = std::make_unique<Word>(Token::ADD, std::vector<char> {});
    auto num2 = std::make_unique<Word>(Token::INT, std::vector<char> { '1', '1' });
    auto mul = std::make_unique<Word>(Token::MUL, std::vector<char> {});
    auto num3 = std::make_unique<Word>(Token::INT, std::vector<char> { '5' });

    words.push_back(std::move(num1));
    words.push_back(std::move(add));
    words.push_back(std::move(num2));
    words.push_back(std::move(mul));
    words.push_back(std::move(num3));

    // Act
    Parser parser;
    auto ast = parser.parse(words);

    // Assert
    EXPECT_FALSE(ast.error);
    EXPECT_EQ(ast.result->opToken, Token::ADD);
    EXPECT_EQ(ast.result->leftNumber->token, Token::INT);
    EXPECT_TRUE(ast.result->rightChild);
    EXPECT_EQ(ast.result->rightChild->opToken, Token::MUL);
    EXPECT_EQ(ast.result->rightChild->leftNumber->token, Token::INT);
    EXPECT_EQ(ast.result->rightChild->rightNumber->token, Token::INT);

    EXPECT_EQ(vector_char_to_string(ast.result->leftNumber->word), "42");
    EXPECT_EQ(vector_char_to_string(ast.result->rightChild->leftNumber->word), "11");
    EXPECT_EQ(vector_char_to_string(ast.result->rightChild->rightNumber->word), "5");
}

//      +
//     / \
//    42  +
//       / \
//      *  111
//     / \
//    /   \
//   11    5
//
// 42 + 11 * 5 + 111
TEST(parse_three_op, add_mul_add) {
    // Arrange
    std::vector<std::unique_ptr<Word>> words;
    auto num1 = std::make_unique<Word>(Token::INT, std::vector<char> { '4' , '2' });
    auto add = std::make_unique<Word>(Token::ADD, std::vector<char> {});
    auto num2 = std::make_unique<Word>(Token::INT, std::vector<char> { '1', '1' });
    auto mul = std::make_unique<Word>(Token::MUL, std::vector<char> {});
    auto num3 = std::make_unique<Word>(Token::INT, std::vector<char> { '5' });
    auto add2 = std::make_unique<Word>(Token::ADD, std::vector<char> {});
    auto num4 = std::make_unique<Word>(Token::INT, std::vector<char> { '1', '1', '1' });

    words.push_back(std::move(num1));
    words.push_back(std::move(add));
    words.push_back(std::move(num2));
    words.push_back(std::move(mul));
    words.push_back(std::move(num3));
    words.push_back(std::move(add2));
    words.push_back(std::move(num4));

    // Act
    Parser parser;
    auto ast = parser.parse(words);

    // Assert
    EXPECT_FALSE(ast.error);
    EXPECT_EQ(ast.result->opToken, Token::ADD);
    EXPECT_EQ(ast.result->leftNumber->token, Token::INT);
    EXPECT_EQ(vector_char_to_string(ast.result->leftNumber->word), "42");

    EXPECT_TRUE(ast.result->rightChild);

    auto rc = ast.result->rightChild;
    EXPECT_EQ(rc->opToken, Token::ADD);
    EXPECT_EQ(vector_char_to_string(rc->rightNumber->word), "111");

    auto rlc = ast.result->rightChild->leftChild;
    EXPECT_TRUE(rlc);
    EXPECT_EQ(rlc->opToken, Token::MUL);

    EXPECT_EQ(vector_char_to_string(rlc->leftNumber->word), "11");
    EXPECT_EQ(vector_char_to_string(rlc->rightNumber->word), "5");
}

//           +
//          / \
//         /   \
//        *     *
//       / \   / \
//      42 11 5  111
//
// 42 * 11 + 5 * 111
TEST(parse_three_op, mul_add_mul) {
    // Arrange
    std::vector<std::unique_ptr<Word>> words;
    auto num1 = std::make_unique<Word>(Token::INT, std::vector<char> { '4' , '2' });
    auto mul = std::make_unique<Word>(Token::MUL, std::vector<char> {});
    auto num2 = std::make_unique<Word>(Token::INT, std::vector<char> { '1', '1' });
    auto add = std::make_unique<Word>(Token::ADD, std::vector<char> {});
    auto num3 = std::make_unique<Word>(Token::INT, std::vector<char> { '5' });
    auto mul2 = std::make_unique<Word>(Token::MUL, std::vector<char> {});
    auto num4 = std::make_unique<Word>(Token::INT, std::vector<char> { '1', '1', '1' });

    words.push_back(std::move(num1));
    words.push_back(std::move(mul));
    words.push_back(std::move(num2));
    words.push_back(std::move(add));
    words.push_back(std::move(num3));
    words.push_back(std::move(mul2));
    words.push_back(std::move(num4));

    // Act
    Parser parser;
    auto ast = parser.parse(words);

    // Assert
    EXPECT_FALSE(ast.error);
    EXPECT_EQ(ast.result->opToken, Token::ADD);
    EXPECT_TRUE(ast.result->rightChild);
    EXPECT_TRUE(ast.result->leftChild);

    auto lc = ast.result->leftChild;
    EXPECT_EQ(lc->opToken, Token::MUL);
    EXPECT_EQ(vector_char_to_string(lc->leftNumber->word), "42");
    EXPECT_EQ(vector_char_to_string(lc->rightNumber->word), "11");

    auto rc = ast.result->rightChild;
    EXPECT_EQ(rc->opToken, Token::MUL);
    EXPECT_EQ(vector_char_to_string(rc->leftNumber->word), "5");
    EXPECT_EQ(vector_char_to_string(rc->rightNumber->word), "111");
}

//
//              +
//             / \
//            /   \
//           /     \
//          1       "/"
//                 /  \
//                /    \
//               ^      2
//              / \
//             /   \
//           3.14 0.123
//
// 1 + 3.14^0.123 / 2
TEST(parse_three_op, with_decimals) {
    // Arrange
    std::vector<std::unique_ptr<Word>> words;
    auto num1 = std::make_unique<Word>(Token::INT, std::vector<char> { '1' });
    auto add = std::make_unique<Word>(Token::ADD, std::vector<char> {});
    auto pi = std::make_unique<Word>(Token::REAL, std::vector<char> { '3', '.', '1', '4' });
    auto pow = std::make_unique<Word>(Token::POWER, std::vector<char> {});
    auto num2 = std::make_unique<Word>(Token::REAL, std::vector<char> { '0', '.', '1', '2', '3' });
    auto div = std::make_unique<Word>(Token::DIV, std::vector<char> {});
    auto num3 = std::make_unique<Word>(Token::INT, std::vector<char> { '2' });

    words.push_back(std::move(num1));
    words.push_back(std::move(add));
    words.push_back(std::move(pi));
    words.push_back(std::move(pow));
    words.push_back(std::move(num2));
    words.push_back(std::move(div));
    words.push_back(std::move(num3));

    // Act
    Parser parser;
    auto ast = parser.parse(words);

    // Assert
    EXPECT_FALSE(ast.error);
    EXPECT_EQ(ast.result->opToken, Token::ADD);

    EXPECT_EQ(vector_char_to_string(ast.result->leftNumber->word), "1");
    EXPECT_TRUE(ast.result->rightChild);

    auto rc = ast.result->rightChild;
    EXPECT_EQ(rc->opToken, Token::DIV);
    EXPECT_EQ(vector_char_to_string(rc->rightNumber->word), "2");
    EXPECT_TRUE(rc->leftChild);

    auto rlc = rc->leftChild;
    EXPECT_EQ(rlc->opToken, Token::POWER);
    EXPECT_EQ(vector_char_to_string(rlc->leftNumber->word), "3.14");
    EXPECT_EQ(vector_char_to_string(rlc->rightNumber->word), "0.123");
}

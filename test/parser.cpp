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

//         +
//        / \
//       /  111
//      +
//     / \
//    42  *
//       / \
//      11  5
//
// 42 + 11 * 5 + 111
TEST(parse_two_op, add_mul_add) {
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
    EXPECT_EQ(ast.result->rightNumber->token, Token::INT);
    EXPECT_EQ(vector_char_to_string(ast.result->rightNumber->word), "111");

    EXPECT_TRUE(ast.result->leftChild);

    auto left_ch = ast.result->leftChild;
    EXPECT_EQ(left_ch->opToken, Token::ADD);
    EXPECT_EQ(vector_char_to_string(left_ch->leftNumber->word), "42");

    auto left_right_ch = ast.result->leftChild->rightChild;
    EXPECT_TRUE(left_right_ch);
    EXPECT_EQ(left_right_ch->opToken, Token::MUL);

    EXPECT_EQ(vector_char_to_string(left_right_ch->leftNumber->word), "11");
    EXPECT_EQ(vector_char_to_string(left_right_ch->rightNumber->word), "5");
}

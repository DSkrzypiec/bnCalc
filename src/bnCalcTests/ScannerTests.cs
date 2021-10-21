using System.Collections.Generic;
using System.Linq;
using Xunit;
using bnCalc;

namespace bnCalcTests
{
    public class ScannerTests
    {
        [Theory]
        [MemberData(nameof(OneOperationTestCases))]
        public void OneOperationTest(string input, List<Token> expectedTokens, List<string> expectedValues)
        {
            // Arrange
            var scanner = new Scanner(input);

            // Act
            var words = scanner.Scan();

            // Assert
            Assert.Equal(expectedTokens.Count, words.Count);
            Assert.Equal(expectedValues.Count, words.Count);
            Assert.Equal(expectedTokens, words.Select(p => p.Token).ToList());
            Assert.Equal(expectedValues, words.Select(p => new string(p.Chars.ToArray())).ToList());
        }

        [Theory]
        [MemberData(nameof(ManyOperationTestCases))]
        public void ManyOperationTest(string input, List<Token> expectedTokens, List<string> expectedValues)
        {
            // Arrange
            var scanner = new Scanner(input);

            // Act
            var words = scanner.Scan();

            // Assert
            Assert.Equal(expectedTokens.Count, words.Count);
            Assert.Equal(expectedValues.Count, words.Count);
            Assert.Equal(expectedTokens, words.Select(p => p.Token).ToList());
            Assert.Equal(expectedValues, words.Select(p => new string(p.Chars.ToArray())).ToList());
        }

        public static IEnumerable<object[]> OneOperationTestCases()
        {
            yield return new object[]
            {
                "1+3",
                new List<Token> { Token.Int, Token.Add, Token.Int },
                new List<string> { "1", "+", "3"}
            };

            yield return new object[]
            {
                "1   \n         +  3  ",
                new List<Token> { Token.Int, Token.Add, Token.Int },
                new List<string> { "1", "+", "3"}
            };

            yield return new object[]
            {
                "1 * 3",
                new List<Token> { Token.Int, Token.Mul, Token.Int },
                new List<string> { "1", "*", "3"}
            };

            yield return new object[]
            {
                "3.14 ^ 1.123e10",
                new List<Token> { Token.Real, Token.Power, Token.Real },
                new List<string> { "3.14", "^", "1.123e10"}
            };
        }

        public static IEnumerable<object[]> ManyOperationTestCases()
        {
            yield return new object[]
            {
                "1+3 * 5.5",
                new List<Token> { Token.Int, Token.Add, Token.Int, Token.Mul, Token.Real },
                new List<string> { "1", "+", "3", "*", "5.5" }
            };

            yield return new object[]
            {
                "(3.14 - 1)  ^ \n 4.1",
                new List<Token> { Token.LParent, Token.Real, Token.Sub, Token.Int, Token.RParent, Token.Power, Token.Real },
                new List<string> { "(", "3.14", "-", "1", ")", "^", "4.1" }
            };
        }
    }
}

using System.Collections.Generic;
using Xunit;
using bnCalc.Models;

namespace bnCalcTests.Models
{
    public class BigIntTests
    {
        [Theory]
        [MemberData(nameof(BigIntCases))]
        public void BigIntConstructionTest(string input, NumSign sign, List<byte> expectedDigits)
        {
            // Act
            var bigInt = new BigInt(input);

            // Assert
            Assert.Equal(expectedDigits.Count, bigInt.Size);
            Assert.Equal(expectedDigits, bigInt.Digits);
            Assert.Equal(sign, bigInt.Sign);
        }

        public static IEnumerable<object[]> BigIntCases()
        {
            yield return new object[] { "1234", NumSign.None, new List<byte> { 1, 2, 3, 4 } };
            yield return new object[] { "1aa234", NumSign.None, new List<byte> { 1, 2, 3, 4 } };
            yield return new object[] { "11213123.123", NumSign.None, new List<byte> { 1, 1, 2, 1, 3, 1, 2, 3, 1, 2, 3} };
            yield return new object[] { "+1234", NumSign.Plus, new List<byte> { 1, 2, 3, 4 } };
            yield return new object[] { "-1234", NumSign.Minus, new List<byte> { 1, 2, 3, 4 } };
            yield return new object[] { "- 1234", NumSign.Minus, new List<byte> { 1, 2, 3, 4 } };
        }
    }
}

using System;
using System.Collections.Generic;

namespace bnCalc.Models
{
    public enum NumSign
    {
        None,
        Plus,
        Minus
    }

    public class BigInt
    {
        public List<byte> Digits { get; init; }
        public long Size { get; init; }
        public NumSign Sign { get; init; }

        public BigInt(string numAsString)
        {
            var digits = new List<byte>(numAsString.Length);
            Sign = NumSign.None;

            if (numAsString.Length > 0)
            {
                if (numAsString[0] == '-')
                    Sign = NumSign.Minus;

                if (numAsString[0] == '+')
                    Sign = NumSign.Plus;
            }

            foreach (char ch in numAsString)
            {
                if (ch >= '0' && ch <= '9')
                {
                    digits.Add((byte)ch);
                }
            }

            Digits = digits;
            Size = digits.Count;
        }
    }
}

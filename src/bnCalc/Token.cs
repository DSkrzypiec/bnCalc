using System.Collections.Generic;

namespace bnCalc
{
    public static class TokenExtensions
    {
        public static bool IsLiteral(this Token token) => token > Token._LiteralsBegin && token < Token._LiteralsEnd;
        public static bool IsOperator(this Token token) => token > Token._OperatorsBegin && token < Token._OperatorsEnd;
    }

    public static class TokenPrecedence
    {
        public static Dictionary<Token, byte> Map()
        {
            return new Dictionary<Token, byte>
            {
                { Token.LParent, 1 },
                { Token.RParent, 1 },
                { Token.Power, 2 },
                { Token.Mul, 3 },
                { Token.Div, 3 },
                { Token.Mod, 3 },
                { Token.Add, 4 },
                { Token.Sub, 4 } 
            };
        }
    }

    /// <summary>
    /// Possible tokens scanned by Scanner.
    /// </summary>
    public enum Token
    {
        Comment,
        Illegal,
        End,

        _LiteralsBegin,
        Int,
        Real,
        _LiteralsEnd,

        _OperatorsBegin,
        Add,        // +
        Sub,        // -
        Mul,        // *
        Div,        // /
        Mod,        // %
        Power,      // ^
        LParent,    // (
        RParent,    // )
        _OperatorsEnd,

        Period      // .
    }
}
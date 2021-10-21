using System.Collections.Generic;

namespace bnCalc.Models
{
    /// <summary>
    /// Word represents single scanned token with corresponding value.
    ///</summary>
    public record Word(Token Token, List<char>? Chars);
}
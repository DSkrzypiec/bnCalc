using System.Collections.Generic;
using bnCalc.Models;

namespace bnCalc
{
    public interface IParser
    {
        ParsingResult Parse(IList<Word> words);
    }

    public class Parser : IParser
    {
        public ParsingResult Parse(IList<Word> words)
        {
            // TODO: Implementation
            var ast = new AST(Token.Illegal);
            return new(ast, null);
        }
    }
}
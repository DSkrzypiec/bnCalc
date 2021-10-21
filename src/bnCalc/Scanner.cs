using System;
using System.Collections.Generic;
using bnCalc.Models;

namespace bnCalc
{
    public interface IScanner
    {
        List<Word> Scan();
    }

    public class Scanner : IScanner
    {
        private readonly string _source;
        private char _current;
        private int _offset = -1;

        public Scanner(string content)
        {
            if (content is null || content.Length == 0)
            {
                _source = "";
                return;
            }

            _source = content;
            _current = _source[0];
            _offset = 0;
        }

        public List<Word> Scan()
        {
            var words = new List<Word>();

            if (_offset == -1)
            {
                return words;
            }

            for (;;)
            {
                var word = ScanSingle();

                if (word.Token == Token.Illegal)
                {
                    throw new ArgumentException($"Got illegal sequence of characters starting from '{word.Chars?.ToString()}'.");
                }

                if (word.Token == Token.End)
                {
                    return words;
                }

                words.Add(word);
            }
        }

        private Word ScanSingle()
        {
            SkipWhiteSpace();

            switch (_current)
            {
                case char.MinValue:
                    return new(Token.End, null);
                case '+':
                    Next();
                    return new(Token.Add, new List<char> { '+' });
                case '-':
                    Next();
                    return new(Token.Sub, new List<char> { '-' });
                case '*':
                    Next();
                    return new(Token.Mul, new List<char> { '*' });
                case '/':
                    Next();
                    return new(Token.Div, new List<char> { '/' });
                case '%':
                    Next();
                    return new(Token.Mod, new List<char> { '%' });
                case '^':
                    Next();
                    return new(Token.Power, new List<char> { '^' });
                case '(':
                    Next();
                    return new(Token.LParent, new List<char> { '(' });
                case ')':
                    Next();
                    return new(Token.RParent, new List<char> { ')' });
            }

            if (char.IsDigit(_current))
            {
                return ScanNumber();
            }

            return new(Token.Illegal, new List<char> { _current });
        }

        private Word ScanNumber()
        {
            var chars = new List<char>();
            var prevChar = _current;
            var token = Token.Int;

            for (;;)
            {
                if (!char.IsDigit(_current) && _current != '.' &&
                    char.ToLower(_current) != 'e' && _current != '+' && _current != '-')
                {
                    break;
                }

                if (_current == '.')
                {
                    token = Token.Real;
                }

                if ((_current == '-' || _current == '+') && (char.ToLower(prevChar) != 'e')) {
                    break;
                }

                prevChar = _current;
                chars.Add(_current);
                Next();
            }

            return new(token, chars);
        }

        private void SkipWhiteSpace()
        {
            while (char.IsWhiteSpace(_current))
            {
                Next();
            }
        }

        private void Next()
        {
            if (_offset + 1 >= _source.Length)
            {
                _offset = _source.Length;
                _current = char.MinValue;
                return;
            }

            _offset++;
            _current = _source[_offset];
        }
    }
}

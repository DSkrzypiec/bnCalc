namespace bnCalc.Models
{
    public class AST
    {
        public Token Token { get; set;}
        public Word? LeftWord { get; set; }
        public Word? RightWord { get; set; }
        public AST? LeftChild { get; set; }
        public AST? RightChild { get; set; }
        public AST? Parent { get; set; }

        public AST(Token tok)
        {
            Token = tok;
        }

        public AST(Token tok, Word leftWord)
        {
            Token = tok;
            LeftWord = leftWord;
        }

        public AST(Token tok, AST leftChild, Word rightWord)
        {
            Token = tok;
            LeftChild = leftChild;
            RightWord = rightWord;
        }

        public AST(Token tok, AST parent, AST leftChild)
        {
            Token = tok;
            Parent = parent;
            LeftChild = leftChild;
        }
    }
}
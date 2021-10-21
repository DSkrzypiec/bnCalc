namespace bnCalc.Models
{
    public record ParsingResult(AST? Result, ParsingError? Error);
    public record ParsingError(int Position, string Message);
}
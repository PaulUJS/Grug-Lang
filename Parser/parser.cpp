#include "parser.h"

unique_ptr<ExprAST> Parser::expression()
{
}

unique_ptr<ExprAST> Parser::equality()
{
    
}

unique_ptr<ExprAST> Parser::comparison()
{

}

unique_ptr<ExprAST> Parser::term()
{

}

unique_ptr<ExprAST> Parser::factor()
{

}

unique_ptr<ExprAST> Parser::unary()
{

}

unique_ptr<ExprAST> Parser::primary()
{

}

unique_ptr<ExprAST> Parser::parse()
{

}

bool Parser::match_token(vector<TokenType> tokens)
{
    for (unsigned int i = 0; i < tokens.size(); i++)
    {
        if (this->check(tokens[i]))
        {
            this->advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType token)
{
    if (this->is_at_end())
        return false;
    return this->peek().tokentype == token;
}

bool Parser::is_at_end()
{
    return this->peek().tokentype == EOFTOK;
}

Token Parser::peek()
{
    return this->tokens[this->index];
}

Token Parser::previous()
{
    return this->tokens[this->index - 1];
}

Token Parser::advance()
{
    if (!this->is_at_end())
        this->index += 1;
    return this->previous();
}

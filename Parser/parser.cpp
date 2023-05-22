#include "parser.h"

unique_ptr<ExprAST> Parser::expression()
{
    return this->equality();
}

unique_ptr<ExprAST> Parser::equality()
{
    return this->comparison();    
}

unique_ptr<ExprAST> Parser::comparison()
{
    return this->term();
}

unique_ptr<ExprAST> Parser::term()
{
    auto expr = this->factor();
    while (this->match_token({PLUS, MINUS}))
    {
        cout << "TERM \n";
        TokenType op = this->previous().tokentype;
        auto right = this->factor();
        expr = make_unique<BinaryExprAST>(op, move(expr), move(right));
    }
    return expr;
}

unique_ptr<ExprAST> Parser::factor()
{
    auto expr = this->primary();
    while (this->match_token({SLASH, STAR}))
    {
        TokenType op = this->previous().tokentype;
        auto right = this->primary();
        expr = make_unique<BinaryExprAST>(op, move(expr), move(right));
    }
    return expr;
}

unique_ptr<ExprAST> Parser::unary()
{
}

unique_ptr<ExprAST> Parser::primary()
{
    if (this->match_token({NUMLIT}))
    {
        cout << "NUMLIT \n";
        return make_unique<NumExprAST>(this->previous().num_val);
    }
}

vector<unique_ptr<ExprAST>> Parser::parse()
{
    vector<unique_ptr<ExprAST>> expr;
    while (!this->is_at_end())
    {
        cout << "parsing \n";
        expr.push_back(this->expression());
    }
    cout << "end parse \n";
    return expr;
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

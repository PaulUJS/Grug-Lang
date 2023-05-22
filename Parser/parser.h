#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>

#include "../Lexer/lexer.h"
#include "../AST/AST.h"

using namespace std;

class Parser 
{
    unique_ptr<ExprAST> expression();
    unique_ptr<ExprAST> equality();
    unique_ptr<ExprAST> comparison();
    unique_ptr<ExprAST> term();
    unique_ptr<ExprAST> factor();
    unique_ptr<ExprAST> unary();
    unique_ptr<ExprAST> primary();

    bool match_token(vector<TokenType> tokens);
    bool check(TokenType token);
    bool is_at_end();

    Token peek();
    Token previous();
    Token advance();

    public: 
        vector<Token> tokens;
        unsigned int index;
        vector<Error> errors;
    
        Parser(vector<Token> tokens, vector<Error> errors) : tokens(tokens), errors(errors) {}
        ~Parser() {};

        vector<unique_ptr<ExprAST>> parse();
};

#endif

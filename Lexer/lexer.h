#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum TokenType 
{
    FN = 0,
    RETURN = 1,

    PLUS = 2,
    MINUS = 3,
    STAR = 4,
    SLASH = 5,
    
    GREATER = 6,
    GREATEREQUAL = 7,
    LESS = 8,
    LESSEQUAL = 9,
    EQUAL = 10,
    EQUALEQUAL = 11,
    BANG = 12,
    BANGEQUAL = 13,

    SEMICOLON = 14,
    COLONCOLON = 15,
    STRLIT = 16,
    NUMLIT = 17,
    LET = 18,

    EOFTOK = 19,

    IDENTIFIER = 20,
    LEFTPAREN = 21,
    RIGHTPAREN = 22,
    NUM = 23,
};

enum ErrorType 
{
    SYNTAXERR = 0,
};

struct Token
{
    TokenType tokentype;
    unsigned int line;
    int num_val;
    string lexeme;
};

struct Error 
{
    string err;
    unsigned int line;
    ErrorType err_type;
};

class Lexer 
{
    void add_token(TokenType token);
    void add_token(TokenType token, int num);
    void add_token(TokenType token, string str);
    void match_token(string& buffer);
    bool writing;

    public:
        vector<Error> errors;
        vector<Token> tokens;
        unsigned int line;

        vector<Token> tokenize();
        void print();
        void print_errors();
};

#endif

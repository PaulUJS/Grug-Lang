#include <iostream>
#include <fstream>

#include "Lexer/lexer.h"
#include "Parser/parser.h"

using namespace std;

vector<Token> lex()
{
    Lexer lexer;
    vector<Token> tokens = lexer.tokenize();
    lexer.print();
    lexer.print_errors();
    return tokens;
}

int main() 
{
    lex(); 
    return 0;
}

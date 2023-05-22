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

    Parser parser(tokens, lexer.errors);
    auto ast = parser.parse();
    cout << ".main \n";
    for (unsigned int i = 0; i < ast.size(); i++)
    {
        cout << ast[i]->code_gen();
        cout << "\n";
    }
    return tokens;
}

int main() 
{
    lex();
    return 0;
}

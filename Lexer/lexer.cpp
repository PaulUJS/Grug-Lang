#include "lexer.h"

vector<Token> Lexer::tokenize()
{
    char ch;
    string buffer;
    bool commenting = false;

    fstream fin("lang.txt", fstream::in);
    while (fin >> noskipws >> ch) 
    { 
        cout << ch;
        if (commenting == true)
        {
            if (ch == '#' || ch == '\n')
                commenting = false;
        }
        else 
        {
            switch (ch)
            {
                case '+': 
                    this->add_token(PLUS);
                    break;
                case '-':
                    this->add_token(MINUS);
                    break;
                case '*':
                    this->add_token(STAR);
                    break;
                case '/':
                    this->add_token(SLASH);
                    break;
                case '"':
                    if (this->writing == false)
                        this->writing = true;
                    else if (this->writing == true)
                        this->add_token(STRLIT, buffer);
                    break;
                case '\n':
                    this->match_token(buffer);
                    this->line += 1;
                    break;
                case ' ':
                    this->match_token(buffer);         
                    break;
                case ';':
                    this->match_token(buffer);
                    this->add_token(SEMICOLON);
                    break;
                case '(':
                    this->add_token(LEFTPAREN);
                    break;
                case ')':
                    this->match_token(buffer);
                    this->add_token(RIGHTPAREN);
                    break;
                case '#':
                    commenting = true;
                    break;
                
                default:
                    buffer.append(1, ch);
                    break;
            }
        }
    }
    this->add_token(EOFTOK);
    return this->tokens;
}

void Lexer::add_token(TokenType token, int num)
{
    this->tokens.push_back({ token, this->line, num, "" });
}

void Lexer::add_token(TokenType token, string str)
{
    this->tokens.push_back({ token, this->line, 0, str });
}

void Lexer::add_token(TokenType token)
{
    this->tokens.push_back({ token, this->line, 0, "" });
}

void Lexer::match_token(string& buffer)
{
    if (buffer.compare("fn") == 0)
        this->add_token(FN, buffer);
    else if (buffer.compare("return") == 0)
         this->add_token(RETURN);
    else if (buffer.compare("=") == 0)
        this->add_token(EQUAL);
    else if (buffer.compare("==") == 0)
        this->add_token(EQUALEQUAL);
    else if (buffer.compare(">") == 0)
        this->add_token(GREATER);
    else if (buffer.compare(">=") == 0)
        this->add_token(GREATEREQUAL);
    else if (buffer.compare("<") == 0)
        this->add_token(LESS);
    else if (buffer.compare("<=") == 0)
        this->add_token(LESSEQUAL);
    else if (buffer.compare("!") == 0)
        this->add_token(BANG);
    else if (buffer.compare("!=") == 0)
        this->add_token(BANGEQUAL);
    else if (buffer.compare("::") == 0)
        this->add_token(COLONCOLON);
    else if (buffer.compare("let") == 0)
        this->add_token(LET);
    else if (buffer.compare("num") == 0)
        this->add_token(NUM);
    else if (buffer.compare("") == 0)
    { 
        buffer.clear();
        return;
    }
    else
    {
        try 
        {
            this->add_token(NUMLIT, stoi(buffer));
        }
        catch (...)
        {   if (this->writing == true)
            {   
                buffer.clear();
                this->writing = false;
                return;
            }
            else
            {
                if (!this->tokens.empty())
                {
                    if (this->tokens.back().tokentype == LET)
                    {
                        this->add_token(IDENTIFIER, buffer);
                        buffer.clear();
                        return;
                    }
                    else if (this->tokens.back().tokentype == FN)
                    {   
                        this->add_token(IDENTIFIER, buffer);
                        buffer.clear();
                        return;
                    }
                    else if (this->tokens.back().tokentype == IDENTIFIER)
                    {
                        this->add_token(IDENTIFIER, buffer);
                        buffer.clear();
                        return;
                    }
                    else if (this->tokens.back().tokentype == RETURN)
                    {
                        this->add_token(IDENTIFIER, buffer);
                        buffer.clear();
                        return;
                    }
                    else if (this->tokens.back().tokentype == EQUAL)
                    {
                        this->add_token(IDENTIFIER, buffer);
                        buffer.clear();
                        return;
                    }
                    else if (this->tokens.back().tokentype == PLUS || this->tokens.back().tokentype == MINUS)
                    {
                        this->add_token(IDENTIFIER, buffer);
                        buffer.clear();
                        return;
                    }
                    else if (this->tokens.back().tokentype == STAR || this->tokens.back().tokentype == SLASH)
                    {
                        this->add_token(IDENTIFIER, buffer);
                        buffer.clear();
                        return;
                    }
                }
            }
            this->errors.push_back({ buffer, this->line, SYNTAXERR });
        }
    }
    buffer.clear();
}

void Lexer::print()
{
    for (unsigned int i = 0; i < this->tokens.size(); i++)
    {
        switch (this->tokens[i].tokentype)
        {
            case 0:
                cout << "FUNCTION \n"; 
                break;
            case 1:
                cout << "RETURN \n";
                break;
            case 2:
                cout << "PLUS \n";
                break;
            case 3:
                cout << "MINUS \n";
                break;
            case 4:
                cout << "STAR \n";
                break;
            case 5:
                cout << "SLASH \n";
                break;
            case 6:
                cout << "GREATER \n";
                break;
            case 7:
                cout << "GREATEREQUAL \n";
                break;
            case 8:
                cout << "LESS \n";
                break;
            case 9:
                cout << "LESSEQUAL \n";
                break;
            case 10:
                cout << "EQUAL \n";
                break;
            case 11:
                cout << "EQUALEQUAL \n";
                break;
            case 12:
                cout << "BANG \n";
                break;
            case 13:
                cout << "BANGEQUAL \n";
                break;
            case 14:
                cout << "SEMICOLON \n";
                break;
            case 15:
                cout << "COLONCOLON \n";
                break;
            case 16:
                cout << "STRLIT" << " " << this->tokens[i].lexeme << "\n";  
                break;
            case 17:
                cout << "NUMLIT" << " " << this->tokens[i].num_val << "\n";
                break;
            case 18:
                cout << "LET \n";
                break;
            case 19:
                cout << "EOF \n";
                break;
            case 20:
                cout << "IDENTIFIER " << this->tokens[i].lexeme << "\n";
                break;
            case 21:
                cout << "LEFT PAREN \n";
                break;
            case 22:
                cout << "RIGHT PAREN \n";
                break;
            case 23:
                cout << "TYPE NUM \n";
                break;
        }
    }
}

void Lexer::print_errors()
{
    for (unsigned int i = 0; i < this->errors.size(); i++)
    {
        cout << "SYNTAX ERROR, UNEXPECTED TOKEN '" << this->errors[i].err << "' " << "on line " << this->errors[i].line << "\n";
    }
}

#include "AST.h"

#include <sstream>

string NumExprAST::code_gen()
{
    stringstream stream;
    stream << "  mov rax, " << this->val << "\n";
    return stream.str();
}

string BinaryExprAST::code_gen()
{
    stringstream stream;
    stream << this->LHS->code_gen() << "  push rax\n" 
        << this->RHS->code_gen() << "  pop rbx\n";
    switch (this->op)
    {
        case PLUS:
            stream << "  add rax, rbx\n";
            break;
        case MINUS:
            break;
        case STAR:
            stream << "  mul rbx\n";
            break;
        case SLASH:
            break;
    }
    return stream.str();
}


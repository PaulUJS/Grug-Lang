#ifndef AST_H
#define AST_H

#include <string>
#include <memory>
#include <iostream>

#include "../Lexer/lexer.h"

using namespace std;

class ExprAST
{
    public:
        virtual ~ExprAST() = default;
        virtual string code_gen() = 0;
};

class NumExprAST : public ExprAST
{
    int val;
    
    public:
        NumExprAST(int val) : val(val) {}
        string code_gen() override;
};

class VarExprAST : public ExprAST 
{
    string name;

    public:
        VarExprAST(const string& name) : name(name) {}
};

class BinaryExprAST : public ExprAST 
{
    TokenType op;
    unique_ptr<ExprAST> LHS, RHS;

    public:
        BinaryExprAST(TokenType op, unique_ptr<ExprAST> LHS,
                unique_ptr<ExprAST> RHS) : op(op), LHS(move(LHS)), RHS(move(RHS)) {}
        string code_gen() override;
};

class CallExprAST : public ExprAST
{
    string called;
    vector<unique_ptr<ExprAST>> args;

    public:
        CallExprAST(const string& called, vector<unique_ptr<ExprAST>> args)
            : called(called), args(move(args)) {}

};

class PrototypeAST 
{
    string name;
    vector<string> args;

    public:
        PrototypeAST(const string& name, vector<string> args) : name(name),
        args(move(args)) {}
        const string& get_name() const { return this->name; }
};

class FunctionAST 
{
    unique_ptr<PrototypeAST> proto;
    unique_ptr<ExprAST> body;

    public:
        FunctionAST(unique_ptr<PrototypeAST> proto, unique_ptr<ExprAST> body)
            : proto(move(proto)), body(move(body)) {}

};

#endif

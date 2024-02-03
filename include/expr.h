#pragma once
#include <parser_node.h>
#include <lexer.h>
#include <string>
#include <vector>
#include<runtime/mc.h>
#include<function.h>
namespace dy
{
    class BinaryNode : public AstNode
    {
    public:
        BinaryNode(TokenType _op, AstNodePtr _lhs, AstNodePtr _rhs) : op(_op), lhs(move(_lhs)), rhs(move(_rhs)) {}
        std::string to_string() const override;
        void code_gen(std::vector<Ins> &ins_set) override;

    private:
        TokenType op;
        AstNodePtr lhs;
        AstNodePtr rhs;
    };
    class Literal : public AstNode
    {
    public:
        Literal(Token _tok);
        Literal(int64_t _val) : val(_val) {}
        std::string to_string() const override;
        void code_gen(std::vector<Ins> &ins_set) override;
    private:
        int64_t val;
    };
    class FunctionCall : public AstNode{
    public:
        FunctionCall(std::string _func_name,int _func_id, std::vector<AstNodePtr>&& _args) : func_name(_func_name),func_id(_func_id), args(std::move(_args)) {}
        std::string to_string() const override;
        void code_gen(std::vector<Ins> &ins_set) override;
        
    private:
        std::string func_name;
        int func_id;
        std::vector<AstNodePtr> args;
    };
    AstNodePtr parse_unit(Scanner &scan);
    AstNodePtr parse_expr(Scanner &scan);
    AstNodePtr parse_normal_binary(Scanner &scan, int ppred);
    AstNodePtr parse_func(Scanner &scan);
}
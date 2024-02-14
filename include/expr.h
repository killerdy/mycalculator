#pragma once
#include <parser_node.h>
#include <lexer.h>
#include <string>
#include <vector>
#include <runtime/mc.h>
#include <function.h>
#include <variant>
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
        std::variant<std::monostate, int64_t, double> obj;
    };
    class Parameter : public AstNode
    {
    public:
        Parameter(std::string _param):param(_param){}
        std::string to_string() const override;
        void code_gen(std::vector<Ins> &ins_set) override;

    private:
        std::string param;
    };
    class UserVar :public AstNode
    {
        public:
        UserVar(std::string _var_name,int _var_id,AstNodePtr _next):var_name(_var_name),var_id(var_id),next(move(_next)){}
        std::string to_string()const override;
        void code_gen(std::vector<Ins> &ins_set)override;
        private:
        std::string var_name;
        int var_id;
        AstNodePtr next;
          
    };
    AstNodePtr parse_unit(Scanner &scan);
    AstNodePtr parse_expr(Scanner &scan);
    AstNodePtr parse_normal_binary(Scanner &scan, int ppred);
    AstNodePtr parse_func(Scanner &scan);
    AstNodePtr parse_symbol(Scanner &scan);
}
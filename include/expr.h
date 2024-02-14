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

    extern std::map<std::string,int> var_table;
    extern int var_table_size;
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
        Parameter(std::string _param) : param(_param) {}
        std::string to_string() const override;
        void code_gen(std::vector<Ins> &ins_set) override;

    private:
        std::string param;
    };
    class UserVar : public AstNode
    {
    public:
        UserVar(std::string _var_name) : var_name(_var_name) {}
        std::string to_string() const override;
        void code_gen(std::vector<Ins> &ins_set) override;
        std::string get_varname()const {return var_name;}
    private:
        std::string var_name;
    };
    AstNodePtr parse_unit(Scanner &scan);
    AstNodePtr parse_expr(Scanner &scan);
    AstNodePtr parse_normal_binary(Scanner &scan, int ppred);
    AstNodePtr parse_func(Scanner &scan);
    AstNodePtr parse_symbol(Scanner &scan);
    AstNodePtr parse_var(Scanner &scan);
}
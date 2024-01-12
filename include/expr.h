#pragma once
#include <lexer.h>
#include <parser_node.h>
#include <string>
#include <vector>
namespace dy
{
    class BinaryNode : public AstNode
    {
    public:
        BinaryNode(TokenType _op, AstNodePtr _lhs, AstNodePtr _rhs)
            : op(_op), lhs(std::move(_lhs)), rhs(std::move(_rhs)) {}
        std::string to_string() const override;
        ObjPtr eval() override;

    private:
        TokenType op;
        AstNodePtr lhs;
        AstNodePtr rhs;
    };
    class Literal : public AstNode
    {
    public:
        Literal(Token _tok);
        Literal(ObjPtr _val) : val(_val) {}
        std::string to_string() const override;

    private:
        ObjPtr val;
    };
    class LocalVar : public AstNode
    {
    public:
        LocalVar(size_t _offset) : offset(_offset) {}
        ObjPtr eval() override;
        std::string to_string() const override
        {
            return "<param " + std::to_string(offset) + ">";
        }

    private:
        size_t offset;
    };
    // AstNodePtr parse_expr();
}
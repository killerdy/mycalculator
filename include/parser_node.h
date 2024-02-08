#pragma once
#include <runtime/mc.h>
#include <string>
#include <vector>
#include <memory>
namespace dy
{
    enum class NodeType : int
    {
        UNKOWN,
        BINOP,
    };
    class AstNode
    {
    public:
        AstNode() {}
        virtual ~AstNode() {}
        AstNode(NodeType nt) : node_type(nt) {}

    public:
        NodeType get_node_type()
        {
            return node_type;
        }
        virtual std::string to_string() const{
            return "<empty node>";
        }
        virtual void code_gen(std::vector<dy::Ins> &ins_set){
            
        }

    private:
        NodeType node_type;
    };
    using AstNodePtr = std::unique_ptr<AstNode>;
}
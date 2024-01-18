#include <runtime/mc.h>
namespace dy
{
    std::vector<int64_t> mem;
    static std::map<Ins::Operator, std::string> ins_map = {
        {Ins::PUSH, "PUSH"},{Ins::ADD, "ADD"},{Ins::SUB, "SUB"},{Ins::MUL, "MUL"},{Ins::DIV, "DIV"}
        };
    
    std::string Ins::to_string()
    {
        if(oper==Ins::PUSH)
            return ins_map[oper]+" "+std::to_string(num);
        return ins_map[oper];
    }
}
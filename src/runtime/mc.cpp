#include <runtime/mc.h>
namespace dy
{
    int fp=0;
    int pc=0;
    int ins_maxn=0;
    void ins_set_clear(){
        while(ins_set.size()>ins_maxn)
        ins_set.pop_back();
    }
    std::vector<dy::Ins> ins_set;
    std::vector<int64_t> mem;
    static std::map<Ins::Operator, std::string> ins_map = {
        {Ins::PUSH, "PUSH"},{Ins::ADD, "ADD"},{Ins::SUB, "SUB"},{Ins::MUL, "MUL"},{Ins::DIV, "DIV"},
        {Ins::PUSH_REL,"PUSH_REL"},{Ins::CALL,"CALL"},{Ins::RET,"RET"}
        };
    
    std::string Ins::to_string()
    {
        // if(oper==Ins::PUSH)
            return ins_map[oper]+" "+std::to_string(num);
        // return ins_map[oper];
    }
}
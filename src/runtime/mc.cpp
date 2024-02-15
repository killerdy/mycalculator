#include <runtime/mc.h>
#include <object.h>
namespace dy
{
    int fp = 0;
    int pc = 0;
    int ins_maxn = 0;
    void ins_set_clear()
    {
        while (ins_set.size() > ins_maxn)
            ins_set.pop_back();
    }
    std::vector<dy::Ins> ins_set;
    std::vector<Object> mem;
    static std::map<Ins::Operator, std::string> ins_map = {
        {Ins::PUSH, "PUSH"},
        {Ins::ADD, "ADD"},
        {Ins::SUB, "SUB"},
        {Ins::MUL, "MUL"},
        {Ins::DIV, "DIV"},
        {Ins::PUSH_REL, "PUSH_REL"},
        {Ins::CALL, "CALL"},
        {Ins::RET, "RET"},
        {Ins::PUSH_VAR, "PUSH_VAR"},
        {Ins::ST_VAR, "ST_VAR"},
        {Ins::PUSH_FUNC,"PUSH_FUNC"},
    };

    std::string Ins::to_string()
    {
        // if(oper==Ins::PUSH)
        // if(oper==Ins::ADD||oper==Ins::SUB||oper==Ins::DIV||oper==Ins::MUL)
        // return ins_map[oper];
        return ins_map[oper] + " " + obj.to_string();
        // return ins_map[oper];
    }
    void Ins::execute()
    {
        switch (oper)
        {
        case PUSH_FUNC:
        {
            std::vector<Object> ve;
            for (int i = 0; i < inter_func_param_cnt[obj.int_val()]; i++)
                ve.push_back(mem.back()), mem.pop_back();
            std::reverse(ve.begin(), ve.end());
            mem.push_back(function_tab[obj.int_val()](ve));
            break;
        }
        case PUSH_VAR:
        {
            mem.push_back(mem[obj.int_val()]);
            break;
        }
        case ST_VAR:
        {

            mem[obj.int_val()] = mem.back();
            // mem.pop_back();
            break;
        }
        case CALL:
        {
            mem.push_back(pc);
            // fp = std::max(var_table.size(), size_t(0));
            mem.push_back(fp);
            fp = mem.size() - 2 - func_param_cnt[obj.int_val()];
            pc = func_ins_pos[obj.int_val()] - 1;
            break;
        }
        case RET:
        {
            Object ret = mem.back();
            mem.pop_back();
            int pre_fp = mem.back().int_val();
            mem.pop_back();

            int next_pc = mem.back().int_val();
            mem.pop_back();

            // mem.resize(max(fp,var_table.size()))
            while (mem.size() > fp && mem.size() > var_table.size())
                mem.pop_back();
            mem.push_back(ret);
            fp = pre_fp;
            pc = next_pc;
            break;
        }
        case PUSH_REL:
            mem.push_back(mem[fp + obj.int_val()]);
            break;
        case PUSH:
            mem.push_back(obj);
            break;
        case ADD:
        {
            auto tmp = mem[mem.size() - 2] + mem[mem.size() - 1];
            mem.pop_back();
            mem.pop_back();
            mem.push_back(tmp);
            break;
        }
        case SUB:
        {
            auto tmp = mem[mem.size() - 2] - mem[mem.size() - 1];
            mem.pop_back();
            mem.pop_back();
            mem.push_back(tmp);
            break;
        }
        case MUL:
        {
            auto tmp = mem[mem.size() - 2] * mem[mem.size() - 1];
            mem.pop_back();
            mem.pop_back();
            mem.push_back(tmp);
            break;
        }
        case DIV:
        {
            auto tmp = mem[mem.size() - 2] / mem[mem.size() - 1];
            mem.pop_back();
            mem.pop_back();
            mem.push_back(tmp);
            break;
        }
        default:
            break;
        }
    }
}
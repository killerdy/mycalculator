#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

namespace dy
{
    class Ins;
    extern int pc;
    extern int fp;
    extern std::vector<dy::Ins> ins_set;
    extern int ins_maxn;
    extern void ins_set_clear();
    extern std::vector<int> func_ins_pos;


    extern int rsp;
    extern std::vector<int> inter_func_param_cnt;
    extern std::vector<int> func_param_cnt;
    extern std::vector<int64_t> mem;
    extern std::vector<std::function<int64_t(std::vector<int64_t>)>> function_tab;

    /*
    fp
    param 1
    param 2
    返回值
    -----指令跳转
    */
    class Ins
    {
    public:
        enum Operator
        {
            PUSH,
            PUSH_REL,
            PUSH_VAR,
            CALL,
            RET,
            ADD,
            SUB,
            MUL,
            DIV,
        };

        Ins(Operator _oper, int _num = 0) : oper(_oper), num(_num) {}
        Ins(int _num) : oper(PUSH), num(_num) {}
        Ins(int _func_id, int x) : oper(PUSH), func_id(_func_id), num(x) {}
        void execute()
        {
            switch (oper)
            {
            case CALL:
            {
                mem.push_back(pc);
                mem.push_back(fp);
                fp = mem.size() - 2 - func_param_cnt[num];
                pc=func_ins_pos[num]-1;
                break;
            }
            case RET:
            {
                int64_t ret = mem.back();
                mem.pop_back();
                int pre_fp = mem.back();
                mem.pop_back();
                
                int next_pc = mem.back();
                mem.pop_back();
                
                while (mem.size() >= fp&&mem.size()>0)
                    mem.pop_back();
                mem.push_back(ret);
                fp = pre_fp;
                pc = next_pc;
                break;
            }
            case PUSH_REL:
                mem.push_back(mem[fp + num]);
                break;
            case PUSH:
                if (func_id == -1)
                    mem.push_back(num);
                else
                {
                    std::vector<int64_t> ve;
                    for (int i = 0; i < inter_func_param_cnt[func_id]; i++)
                        ve.push_back(mem.back()), mem.pop_back();
                    std::reverse(ve.begin(), ve.end());
                    mem.push_back(function_tab[func_id](ve));
                }
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
        std::string to_string();

    private:
        Operator oper;
        int64_t num;
        int func_id = -1;
    };

}
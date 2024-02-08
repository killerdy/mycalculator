#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

namespace dy
{
    class Ins;
    extern int rsp;
    extern std::vector<int> func_param_cnt;
    extern std::vector<int64_t> mem;
    extern std::vector<std::function<int64_t(std::vector<int64_t>)>> function_tab;
    class Ins
    {
    public:
        enum Operator
        {
            PUSH,
            ADD,
            SUB,
            MUL,
            DIV,
        };

        Ins(Operator _oper) : oper(_oper) {}
        Ins(int _num) : oper(PUSH), num(_num) {}
        Ins(int _func_id, int x) : oper(PUSH), func_id(_func_id) {}
        void execute()
        {
            switch (oper)
            {
            case PUSH:
                if (func_id == -1)
                    mem.push_back(num);
                else
                {
                    std::vector<int64_t> ve;
                    for (int i = 0; i < func_param_cnt[func_id]; i++)
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
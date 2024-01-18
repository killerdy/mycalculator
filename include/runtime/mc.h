#pragma once
#include <vector>
#include <string>
#include<map>
#include<iostream>
namespace dy
{
    extern std::vector<int64_t> mem;
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
        void execute()
        {
            switch (oper)
            {
            case PUSH:
                mem.push_back(num);
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
    };

}
#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cinttypes>
#include <object.h>
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
    extern std::vector<Object> mem;
    extern std::vector<std::function<Object(std::vector<Object>)>> function_tab;
    extern std::map<std::string, int> var_table;

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
            PUSH_FUNC,
            ST_VAR,
            CALL,
            RET,
            ADD,
            SUB,
            MUL,
            DIV,
        };

        Ins(Operator _oper, Object _obj) : oper(_oper), obj(_obj) {}
        Ins(Operator _oper) : oper(_oper) {}
        // Ins( _num) : oper(PUSH), num(_num) {}
        // Ins(int _func_id, int x) : oper(PUSH), func_id(_func_id), num(x) {}
        void execute();
        std::string to_string();

    private:
        Operator oper;
        Object obj;
        // int func_id = -1;
    };

}
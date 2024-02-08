#pragma once
#include <memory>
#include <expr.h>
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <parser_node.h>

namespace dy
{
    extern std::vector<std::function<int64_t(std::vector<int64_t>)>> function_tab;
    extern std::vector<int> func_param_cnt;
    extern std::map<std::string, int> inter_function_id_tab;
    extern std::map<std::string,int> function_param_id_tab;
    class FunctionCall : public AstNode{
    public:
        FunctionCall(std::string _func_name,int _func_id, std::vector<AstNodePtr>&& _args,bool _userdefine = false) : func_name(_func_name),func_id(_func_id), args(std::move(_args)),userdefine(_userdefine) {}
        std::string to_string() const override;
        void code_gen(std::vector<Ins> &ins_set) override;
        
    private:
        bool userdefine = false;
        std::string func_name;
        int func_id;
        std::vector<AstNodePtr> args;
    };
    
    void set_basic_inter();
}
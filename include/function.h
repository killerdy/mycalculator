#pragma once
#include <memory>
#include <expr.h>
#include <string>
#include <functional>
#include <vector>
#include <map>

namespace dy
{
    class AstNode;
    using AstNodePtr = std::unique_ptr<AstNode>;
    extern std::vector<std::function<int64_t(std::vector<int64_t>)>> function_tab;
    extern std::vector<int> func_param_cnt;
    extern std::map<std::string, int> inter_function_id_tab;
    // class InterCall : public FunctionCall
    // {
    // public:
    // private:
    // };

    void set_basic_inter();

}
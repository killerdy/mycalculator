#include <function.h>
#include <vector>
#include <cmath>

namespace dy
{
    int64_t inter_sin(const std::vector<int64_t> &args)
    {
        return sin(args[0]);
    }
    int64_t dy_add2(const std::vector<int64_t> &args){
        return args[0]+args[1];
    }
    int64_t dy_add3(const std::vector<int64_t> &args){
        return args[0]+args[1]+args[2];
    }
    int64_t dy_div2(const std::vector<int64_t> &args){
        return args[0]/args[1];
    }
    int64_t inter_cos(const std::vector<int64_t> &args){
        return cos(args[0]);
    }
    void set_basic_inter()
    {
        function_tab.push_back(inter_sin);
        function_tab.push_back(inter_cos);
        function_tab.push_back(dy_add2);
        function_tab.push_back(dy_add3);
        function_tab.push_back(dy_div2);
        inter_func_param_cnt.push_back(1);
        inter_func_param_cnt.push_back(1);
        inter_func_param_cnt.push_back(2);
        inter_func_param_cnt.push_back(3);
        inter_func_param_cnt.push_back(2);
        int id=0;
        inter_function_id_tab["sin"]=id++;
        inter_function_id_tab["cos"]=id++;
        inter_function_id_tab["dy_add2"]=id++;
        inter_function_id_tab["dy_add3"]=id++;
        inter_function_id_tab["dy_div2"]=id++;
    }
}

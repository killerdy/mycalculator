#include <function.h>
#include <vector>
#include <cmath>

namespace dy
{
    Object inter_sin(const std::vector<Object> &args)
    {
        return sin(args[0].double_val());
    }
    Object inter_tan(const std::vector<Object> &args)
    {
        return tan(args[0].double_val());
    }
    Object inter_pow(const std::vector<Object> &args)
    {
        return pow(args[0].double_val(),args[1].double_val());
    }
    Object dy_add2(const std::vector<Object> &args){
        return args[0]+args[1];
    }
    Object dy_add3(const std::vector<Object> &args){
        return args[0]+args[1]+args[2];
    }
    Object dy_div2(const std::vector<Object> &args){
        return args[0]/args[1];
    }
    Object inter_cos(const std::vector<Object> &args){
        return cos(args[0].double_val());
    }
    void set_basic_inter()
    {
        function_tab.push_back(inter_sin);
        function_tab.push_back(inter_cos);
        function_tab.push_back(inter_tan);
        function_tab.push_back(inter_pow);

        function_tab.push_back(dy_add2);
        function_tab.push_back(dy_add3);
        function_tab.push_back(dy_div2);


        inter_func_param_cnt.push_back(1);
        inter_func_param_cnt.push_back(1);
        inter_func_param_cnt.push_back(1);
        inter_func_param_cnt.push_back(2);

        inter_func_param_cnt.push_back(2);
        inter_func_param_cnt.push_back(3);
        inter_func_param_cnt.push_back(2);
        int id=0;

        inter_function_id_tab["sin"]=id++;
        inter_function_id_tab["cos"]=id++;
        inter_function_id_tab["tan"]=id++;
        inter_function_id_tab["pow"]=id++;
        
        inter_function_id_tab["dy_add2"]=id++;
        inter_function_id_tab["dy_add3"]=id++;
        inter_function_id_tab["dy_div2"]=id++;
    }
}

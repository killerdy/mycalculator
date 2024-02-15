#include <iostream>
#include <lexer.h>
#include <string>
#include <expr.h>
#include <runtime/mc.h>
#include <utils.h>

int main()
{
    using namespace dy;
    // dy_error(FATAL_ERROR,"dayyun");

    std::string s;
    dy::Scanner a;
    dy::set_basic_inter();
    while (std::getline(std::cin, s))
    {
        while (s == "")
            std::cin >> s;
        if (s == "exit")
            break;
        while(dy::mem.size()>var_table.size())
            dy::mem.pop_back();
        a.set_content(s);
        a.scan();
        // a.print_tokens();
        // printf("\n===================================\n");
        auto root = parse_expr(a);
        // std::cout << (root->to_string())<<"\n";
        // std::vector<dy::Ins> ins_set;
        
        root->code_gen(ins_set);
        // for(auto it:ins_set)
        // {
        //     std::cout<<it.to_string()<<"\n";
        // }
        for (pc = ins_maxn; pc < ins_set.size(); pc++)
        {
            // std::cout << ins_set[pc].to_string() << "\n";
            
            ins_set[pc].execute();
        }
        // for(int pc = 0;pc<ins_set.size();pc++)
        // {

        // }
        // for(auto it:ins_set)
        // {
        //     std::cout<<it.to_string()<<"\n";
        //     it.execute();
        // }
        // printf("===================================\n");
        
        // std::cout<<"RESULT :";
        
        // for(auto v:mem)
        // {
        //     std::cout<<v<<" ";
        // }
        // std::cout<<std::endl;
        if (mem.size() > var_table.size())
            std::cout<<"RESULT: "<<dy::mem.back().to_string()<<"\n";
        ins_set_clear();
    }
    return 0;
}
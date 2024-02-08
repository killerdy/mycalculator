#include<iostream>
#include<lexer.h>
#include<string>
#include<expr.h>
#include<runtime/mc.h>
#include<utils.h>

int main(){
    using namespace dy;
    // dy_error(FATAL_ERROR,"dayyun");
    std::string s;
    dy::Scanner a;
    dy::set_basic_inter();
    while(std::getline(std::cin,s))
    {
        while(s=="")
        std::cin>>s;
        if(s=="exit")
        break;
        dy::mem.clear();
        a.set_content(s);
        a.scan();
        // a.print_tokens();
        // printf("\n===================================\n");
        auto root=parse_expr(a);
        // std::cout<<(root->to_string());
        // printf("\n===================================\n");
        // std::vector<dy::Ins> ins_set;
        
        root->code_gen(ins_set);
        // for(auto it:ins_set)
        // {
        //     std::cout<<it.to_string()<<"\n";
        // }
        // printf("\n===================================\n");
        for(pc=ins_maxn;pc<ins_set.size();pc++)
        {
            // std::cout<<ins_set[pc].to_string()<<"\n";
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
        if(mem.size())
        printf("RESULT: %ld\n",dy::mem[0]);
        // std::cout<<mem.size()<<std::endl;
        ins_set_clear();
    }
    return 0;
}
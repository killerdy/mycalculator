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
        a.print_tokens();
        printf("\n===================================\n");
        auto root=parse_expr(a);
        std::cout<<(root->to_string());
        printf("\n===================================\n");
        std::vector<dy::Ins> ins_set;
        root->code_gen(ins_set);
        for(auto it:ins_set)
        {
            std::cout<<it.to_string()<<"\n";
            it.execute();
        }
        printf("===================================\n");
        printf("RESULT: %ld\n",dy::mem[0]);
    }
    return 0;
}
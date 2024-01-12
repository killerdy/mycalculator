#include<iostream>
#include<lexer.h>
int main(){
    std::string s;
    dy::Scanner a;
    while(std::getline(std::cin,s))
    {
        
        a.set_content(s);
        a.scan();
        a.print_tokens();
        std::cout<<std::endl;
        
    }
}
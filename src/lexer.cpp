#include <lexer.h>
#include <iostream>
namespace dy
{
    std::map<std::string, TokenType> keywords = {
        {"+", TokenType::ADD}, {"-", TokenType::SUB}, {"*", TokenType::MUL}, {"/", TokenType::DIV}, {"(", TokenType::LPAR}, {")", TokenType::RPAR}};
    void Scanner::scan()
    {
        size_t &i = content_pos;
        for (; i < content.size(); i++)
            switch (content[i])
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '(':
            case ')':
                tokens.push_back(Token(keywords[std::string(1, content[i])]));
                continue;
            default:
                if (isdigit(content[i]))
                    tokens.push_back(parse_number(content, content_pos));
                break;
            }
    }
    Token Scanner::parse_number(const std::string &str, size_t &i)
    {
        unsigned long long ret = 0;
        int base = 10;
        while (i < str.size() && isdigit(str[i]))
        {
            ret = ret * base + str[i] - 48;
            i++;
        }
        i--;
        return Token((int64_t)ret, TokenType::INT);
    }
    void Scanner::set_content(const std::string &s)
    {
        content = s;
        tokens.clear();
        content_pos = 0;
    }
    void Scanner::print_tokens()
    {
        // std::cout<<tokens.size();
        for (auto it : tokens)
        {
            printf("<%d> ", (int)(it.get_type()));
        }
    }
}
#include <lexer.h>
#include <iostream>
#include <utils.h>
namespace dy
{
    std::map<std::string, TokenType> keywords = {
        {"+", TokenType::ADD}, {"-", TokenType::SUB}, {"*", TokenType::MUL}, {"/", TokenType::DIV}, {"(", TokenType::LPAR}, {")", TokenType::RPAR}};
    std::map<TokenType, std::string> rkeywords={
        {TokenType::ADD,"+"},{TokenType::SUB,"-"},{TokenType::MUL,"*"},{TokenType::DIV,"/"},{TokenType::LPAR,"()"},{TokenType::RPAR,")"}
    };
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
        pos=0;
    }
    void Scanner::print_tokens()
    {
        for (auto it : tokens)
        {
            printf("<");
            switch (it.get_type())
            {
            case TokenType::ADD:
                printf("ADD");
                break;
            case TokenType::SUB:
                printf("SUB");
                break;
            case TokenType::MUL:
                printf("MUL");
                break;
            case TokenType::DIV:
                printf("DIV");
                break;
            case TokenType::LPAR:
                printf("LPAR");
                break;
            case TokenType::RPAR:
                printf("RPAR");
                break;
            case TokenType::INT:
                printf("INT %ld", it.get_value<int64_t>());
                break;
            }
            printf("> ");
        }
    }
    Token Scanner::this_token()
    {
        return tokens[pos];
    }
    void Scanner::match(TokenType tag)
    {
        if (this_token().get_type() != tag)
            dy_error(SYNTAX_ERROR, "aa");
        advance();
    }
    void Scanner::advance()
    {
        pos++;
        if (pos >= tokens.size())
        {
            tokens.push_back(TokenType::ENDTOKEN);
        }
    }
    TokenType Scanner::cur_tag() { return this_token().get_type(); }
}
#include <lexer.h>
#include <iostream>
#include <utils.h>
namespace dy
{
    std::map<std::string, TokenType> keywords = {
        {"+", TokenType::ADD}, {"-", TokenType::SUB}, {"*", TokenType::MUL}, {"/", TokenType::DIV}, {"(", TokenType::LPAR}, {")", TokenType::RPAR}, 
        {",", TokenType::COMMA},{"=",TokenType::ASSIGN}};
    std::map<TokenType, std::string> rkeywords = {
        {TokenType::ADD, "+"}, {TokenType::SUB, "-"}, {TokenType::MUL, "*"}, {TokenType::DIV, "/"}, {TokenType::LPAR, "()"}, {TokenType::RPAR, ")"},
        {TokenType::COMMA, ","},{TokenType::ASSIGN,"="}};
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
            case ',':
            case '=':
                tokens.push_back(Token(keywords[std::string(1, content[i])]));
                continue;
            default:
                if (content[i] == '_' || isalpha(content[i]))
                    tokens.push_back(parse_word(content, i));
                else if (isdigit(content[i]))
                    tokens.push_back(parse_number(content, content_pos));
                break;
            }
    }
    Token Scanner::parse_word(const std::string &content, size_t &i)
    {
        std::string symbol;
        while (i < content.size() && (content[i] == '_' || isalnum(content[i])))
            symbol += content[i++];
        i--;
        auto it = keywords.find(symbol);
        if (it == keywords.end())
            return Token(symbol, TokenType::SYMBOL);
        return Token({}, it->second);
    }
    double parse_float(int base, double val, const std::string &str, size_t &i, Scanner &scanner)
    {
        double sum = 1;
        double ans = 0;
        i++;
        while (i < str.size() && isdigit(str[i]))
        {
            sum *= base;
            ans = ans * base + (str[i++] - 48);
        }
        return val + ans / sum;
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
        if (str[i] == '.')
        {
            double val = parse_float(base, ret, str, i, *this);
            i--;
            return Token(val, TokenType::DOUBLE);
        }
        i--;
        return Token((int64_t)ret, TokenType::INT);
    }

    void Scanner::set_content(const std::string &s)
    {
        content = s;
        tokens.clear();
        content_pos = 0;
        pos = 0;
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
            case TokenType::SYMBOL:
                printf("SYMBOL %s", it.get_value<std::string>().c_str());
                break;
            case TokenType::DOUBLE:
                printf("DOUBLE %lf", it.get_value<double>());
                break;
            }
            printf("> ");
        }
    }
    Token Scanner::this_token()
    {
        return tokens[pos];
    }
    Token Scanner::next_token(){
        return tokens[pos+1];
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
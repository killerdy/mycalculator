#pragma once
#include <string>
#include <vector>
#include <map>
#include<cinttypes>
#include <variant>
namespace dy
{
    enum class TokenType : int
    {
        ENDTOKEN,
        ASSIGN,
        COMMA,
        SYMBOL,
        INT,
        DOUBLE,
        ADD,
        SUB,
        MUL,
        DIV,
        LPAR,RPAR
    };
    class Token
    {
    public:
        using TokenValue = std::variant<std::monostate, std::string, int64_t,double>;
        Token(const TokenValue &_value, const TokenType &_type) : value(_value), type(_type) {}
        Token(const TokenType &_type) : type(_type) {}
        template <typename T>
        T get_value() { return std::get<T>(value); }
        TokenType get_type() { return type; }

    private:
        TokenType type;
        TokenValue value;
    };
    class Scanner
    {
    public:
        Scanner() : content(""), filename("noname") {}
        // Scanner(){}
        Scanner(const std::string &_content) : content(_content), filename("noname") {}
        Token parse_number(const std::string &content, size_t &pos);
        Token parse_word(const std::string &content,size_t &i);
        void set_content(const std::string &s);
        void print_tokens();
        void scan();
        void match(TokenType tag);
        Token this_token();
        Token next_token();
        void advance();
        TokenType cur_tag();
        bool is_terminal() { return cur_tag() == TokenType::ENDTOKEN; }
    private:
        std::string content;
        std::string filename;
        std::vector<Token> tokens;
        int pos = 0;
        size_t content_pos = 0;
    };
}
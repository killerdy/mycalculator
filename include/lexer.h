#include <string>
#include <vector>
#include <map>
#include <variant>
namespace dy
{
    enum class TokenType : int
    {
        ENDTOKEN,
        INT,
        ADD,
        SUB,
        MUL,
        DIV,
        LPAR,RPAR
    };
    class Token
    {
    public:
        using TokenValue = std::variant<std::monostate, std::string, int64_t>;
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
        void set_content(const std::string &s);
        void print_tokens();
        void scan();

    private:
        std::string content;
        std::string filename;
        std::vector<Token> tokens;
        int pos = 0;
        size_t content_pos = 0;
    };
}
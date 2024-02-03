#include <function.h>
#include <expr.h>
#include<function.h>
namespace dy
{
    std::vector<std::function<int64_t(std::vector<int64_t>)>> function_tab;
    std::vector<int> func_param_cnt;
    std::map<std::string, int> inter_function_id_tab;

    AstNodePtr parse_func(Scanner &scan)
    {
        auto tok = scan.this_token();
        scan.match(TokenType::SYMBOL);
        auto func_name = tok.get_value<std::string>();
        scan.match(TokenType::LPAR);
        std::vector<AstNodePtr> args;
        while (scan.cur_tag() != TokenType::RPAR)
        {
            args.push_back(std::move(parse_expr(scan)));
            if (scan.cur_tag() == TokenType::COMMA)
                scan.match(TokenType::COMMA);
        }
        scan.match(TokenType::RPAR);
        return std::make_unique<FunctionCall>(func_name, inter_function_id_tab[func_name], std::move(args));
        // return nullptr;
    }
    std::string FunctionCall::to_string() const
    {
        std::string ret = func_name + "(";
        for (auto &it : args)
        {
            ret += it->to_string();
            if (it != args.back())
                ret += ",";
        }
        ret += ") ";
        return ret;
    }
    void FunctionCall::code_gen(std::vector<Ins> &ins_set)
    {
        for (const auto &it : args)
        {
            it->code_gen(ins_set);
        }
        ins_set.push_back(Ins(func_id, 1));
    }

}
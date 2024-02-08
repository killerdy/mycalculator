#include <function.h>
#include <expr.h>
namespace dy
{
    std::vector<std::function<int64_t(std::vector<int64_t>)>> function_tab;
    std::vector<int> inter_func_param_cnt;
    std::vector<int> func_param_cnt;
    std::map<std::string, int> inter_function_id_tab;
    std::map<std::string, int> function_param_id_tab;
    std::map<std::string, int> function_id_tab;
    int function_id_maxn = 0;

    std::vector<int> func_ins_pos;
    // std::vector<int> func_ins_num;

    AstNodePtr parse_func(Scanner &scan)
    {
        auto tok = scan.this_token();
        scan.match(TokenType::SYMBOL);
        auto func_name = tok.get_value<std::string>();
        scan.match(TokenType::LPAR);

        if (inter_function_id_tab.count(func_name))
        {
            std::vector<AstNodePtr> args;
            while (scan.cur_tag() != TokenType::RPAR)
            {
                args.push_back(std::move(parse_expr(scan)));
                if (scan.cur_tag() == TokenType::COMMA)
                    scan.match(TokenType::COMMA);
            }
            scan.match(TokenType::RPAR);
            return std::make_unique<FunctionCall>(func_name, inter_function_id_tab[func_name], std::move(args));
        }
        else if (function_id_tab.count(func_name))
        {
            std::vector<AstNodePtr> args;
            while (scan.cur_tag() != TokenType::RPAR)
            {
                args.push_back(std::move(parse_expr(scan)));
                if (scan.cur_tag() == TokenType::COMMA)
                    scan.match(TokenType::COMMA);
            }
            scan.match(TokenType::RPAR);
            return std::make_unique<FunctionCall>(func_name, function_id_tab[func_name], std::move(args), true);
        }
        else
        {

            function_param_id_tab.clear();
            int id = 0;
            while (scan.cur_tag() != TokenType::RPAR)
            {
                auto cur_tok = scan.this_token();
                scan.match(TokenType::SYMBOL);
                auto cur_name = cur_tok.get_value<std::string>();
                function_param_id_tab[cur_name] = id++;
                if (scan.cur_tag() == TokenType::COMMA)
                    scan.match(TokenType::COMMA);
            }
            
            function_id_tab[func_name] = function_id_maxn;
            
            func_param_cnt.push_back(id);
            function_id_maxn++;

            scan.match(TokenType::RPAR);
            scan.match(TokenType::ASSIGN);
            
            return std::make_unique<FunctionDefine>(func_name, function_id_maxn - 1, parse_expr(scan));
        }

        // return nullptr;
    }
    std::string FunctionDefine::to_string() const
    {
        return "functionDefine "+arg->to_string();
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
        if (userdefine)
        {
            for (const auto &it : args)
                it->code_gen(ins_set);
            ins_set.push_back(Ins(Ins::CALL, func_id));
        }
        else
        {
            for (const auto &it : args)
            {
                it->code_gen(ins_set);
            }
            ins_set.push_back(Ins(func_id, 100));
        }
    }
    void FunctionDefine::code_gen(std::vector<Ins> &ins_set)
    {
        // func_ins_pos[func_id] = ins_set.size();
        func_ins_pos.push_back(ins_set.size());
        arg->code_gen(ins_set);
        
        ins_set.push_back(Ins(Ins::RET));
        ins_maxn = ins_set.size();
        
    }

}
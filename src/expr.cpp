#include <expr.h>
#include <vector>
#include <lexer.h>
#include <utils.h>
#include <function.h>
#include <map>
namespace dy
{

    extern std::map<TokenType, std::string> rkeywords;
    int var_table_size=0;
    std::map<std::string, int> var_table;
    AstNodePtr parse_unit(Scanner &scan)
    {
        auto cur_tok = scan.this_token();
        switch (cur_tok.get_type())
        {
        case TokenType::LPAR:
        {
            scan.match(TokenType::LPAR);
            auto ret = parse_expr(scan);
            scan.match(TokenType::RPAR);
            return ret;
        }
        case TokenType::SYMBOL:
        {
            return parse_symbol(scan);
            // return parse_func(scan);
        }
        case TokenType::INT:
        {
            scan.advance();
            return std::make_unique<Literal>(cur_tok);
        }
        case TokenType::DOUBLE:
        {
        }
        default:
            dy_error(SYNTAX_ERROR, "unsupport unit");
        }
        return nullptr;
    }
    AstNodePtr parse_symbol(Scanner &scan)
    {
        auto tok = scan.this_token();
        auto cur_name = tok.get_value<std::string>();
        if (function_param_id_tab.count(cur_name))
        {
            scan.advance();
            return std::make_unique<Parameter>(cur_name);
        }
        if (scan.next_token().get_type() != TokenType::LPAR)
        {
            return parse_var(scan);
        }
        return parse_func(scan);

        // scan.match(TokenType::SYMBOL);
        // auto symbol_name=tok.get_value<std::string>();
    }
    AstNodePtr parse_var(Scanner &scan)
    {

        auto tok = scan.this_token();
        scan.match(TokenType::SYMBOL);
        auto var_name = tok.get_value<std::string>();

        return std::make_unique<UserVar>(var_name);
    }
    AstNodePtr parse_expr(Scanner &scan)
    {

        return parse_normal_binary(scan, 15);
    }
    AstNodePtr parse_normal_binary(Scanner &scan, int ppred)
    {

        if (ppred == 1)
            return parse_unit(scan);
        static std::map<TokenType, std::pair<int, bool>> pred_tab = {
            {TokenType::ADD, {4, true}},
            {TokenType::SUB, {4, true}},
            {TokenType::MUL, {3, true}},
            {TokenType::DIV, {3, true}},
            {TokenType::ASSIGN, {10, false}},

        };
        auto get_pred = [&](TokenType tag) -> std::pair<int, bool>
        {
            auto it = pred_tab.find(tag);
            if (it == pred_tab.end())
                return {100, false};
            return it->second;
        };
        auto left = parse_normal_binary(scan, ppred - 1);
        std::vector<AstNodePtr> nodes;
        nodes.push_back(std::move(left));
        std::vector<TokenType> ops;
        while (!scan.is_terminal() && get_pred(scan.cur_tag()).first == ppred)
        {
            auto op = scan.cur_tag();
            scan.advance();
            ops.push_back(op);
            auto right = parse_normal_binary(scan, ppred - 1);
            nodes.emplace_back(std::move(right));
        }
        if (nodes.size() == 1)
            return std::move(nodes.front());

        if (get_pred(scan.cur_tag()).second)
        {
            AstNodePtr root = std::move(nodes.front());
            for (int i = 1; i < nodes.size(); i++)
            {
                root = std::make_unique<BinaryNode>(ops[i - 1], std::move(root), std::move(nodes[i]));
            }
            return root;
        }
        else
        {
            AstNodePtr root = std::move(nodes.back());
            for (int i = ops.size() - 1; i >= 0; i--)
            {
                root = std::make_unique<BinaryNode>(ops[i], std::move(nodes[i]), std::move(root));
            }
            return root;
        }
    }
    std::string BinaryNode::to_string() const
    {
        return "(" + rkeywords[op] + " " + lhs->to_string() + " " + rhs->to_string() + ")";
    }
    std::string Literal::to_string() const
    {
        return std::to_string(val);
    }
    Literal::Literal(Token tok)
    {
        if (tok.get_type() == TokenType::INT)
            val = tok.get_value<int64_t>();
        else if (tok.get_type() == TokenType::DOUBLE)
            obj = tok.get_value<double>();
    }
    void BinaryNode::code_gen(std::vector<Ins> &ins_set)
    {

        if (op == TokenType::ASSIGN)
        {
            std::string cur_name = static_cast<UserVar *>(lhs.get())->get_varname();
            if (!var_table.count(cur_name)) // is =
            {
                var_table[cur_name] = var_table.size();
                ins_set.push_back(Ins(0));
            }
            rhs->code_gen(ins_set);
            ins_set.push_back(Ins(Ins::ST_VAR, var_table[cur_name]));
            return;
        }
        lhs->code_gen(ins_set);
        rhs->code_gen(ins_set);
        switch (op)
        {
        case TokenType::ADD:
            ins_set.push_back(Ins(Ins::ADD));
            break;
        case TokenType::SUB:
            ins_set.push_back(Ins(Ins::SUB));
            break;
        case TokenType::MUL:
            ins_set.push_back(Ins(Ins::MUL));
            break;
        case TokenType::DIV:
            ins_set.push_back(Ins(Ins::DIV));
            break;
        default:
            break;
        }
    }
    void Literal::code_gen(std::vector<Ins> &ins_set)
    {
        ins_set.push_back(Ins(val));
    }
    std::string Parameter::to_string() const
    {
        return param;
    }
    void Parameter::code_gen(std::vector<Ins> &ins_set)
    {
        ins_set.push_back(Ins(Ins::PUSH_REL, function_param_id_tab[param]));
    }
    std::string UserVar::to_string() const
    {
        return var_name;
    }
    void UserVar::code_gen(std::vector<Ins> &ins_set)
    {

        ins_set.push_back(Ins(Ins::PUSH_VAR, var_table[var_name]));
    }
}
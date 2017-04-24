/* author: dongchangzhang */
/* time: 2017年04月20日 星期四 18时27分33秒 */

#include "translate.h"
#include "parser.h"
#include <iostream>

void Translater::action_run(Parser& parser, std::string& action, std::string& which, size_t index)
{
    action_which = which;
    action_index = index;
    action_production = parser.grammar.get_production(which, index);
    if (action == "action_CALC") {
        action_CALC(parser);
    } else if (action == "action_ID") {
        action_ID(parser);
    } else if (action == "action_SWAP") {
        action_SWAP(parser);
    } else if (action == "action_VE") {
        action_VE(parser);
    } else if (action == "action_VT") {
        action_VT(parser);
    } else if (action == "action_value_declare") {
        action_value_declare(parser);
    } else if (action == "action_value_define") {
        action_value_define(parser);
    } else {
        std::cout << "ELSE -> Translater" << std::endl;
        // pop
        for (size_t i = 0; i < action_production.size(); ++i) {
            parser.token_stack.pop();
            parser.status_stack.pop();
        }
    }
}
template <typename T1, typename T2, typename T3>
void Translater::generate_code(T1& value1, T2& value2, T3& op)
{
    std::cout << timer_increase() << " : ";
    std::cout << value1 << " " << value1 << " " << op << std::endl;
}
template <typename T1, typename T2, typename T3>
T1 Translater::calcu_exp(T1& value1, T2& value2, T3& op)
{
    if (value1.type == value2.type && value1.type == VOL_IS_NUM_VALUE)
        value1.ivol += value2.ivol;
    return value1;
}
void Translater::action_CALC(Parser& parser)
{
    std::cout << "CALC -> Translater" << std::endl;

    auto value2 = parser.vol_stack.top();
    parser.vol_stack.pop();
    parser.token_stack.pop();
    parser.status_stack.pop();

    auto op = parser.token_stack.top();
    parser.token_stack.pop();
    parser.status_stack.pop();

    auto value1 = parser.vol_stack.top();
    parser.vol_stack.pop();
    parser.token_stack.pop();
    parser.status_stack.pop();

    auto result = calcu_exp(value1, value2, op);
    parser.vol_stack.push(result);
    std::cout << result.ivol << std::endl;
    generate_code(value1, value2, op);
}
void Translater::action_ID(Parser& parser)
{

    std::cout << "ID -> Translater" << std::endl;
    // pop
    Parser::vol_type vol;
    auto token = parser.token_stack.top();
    vol.type = VOL_IS_ID;
    vol.svol = token.get_attr();
    parser.token_stack.pop();
    parser.status_stack.pop();
    parser.vol_stack.push(vol);
}

void Translater::action_SWAP(Parser& parser)
{

    std::cout << "SWAP -> Translater" << std::endl;
    // pop
    parser.token_stack.pop();
    parser.status_stack.pop();
}
void Translater::action_VE(Parser& parser)
{
    std::cout << "VE -> Translater" << std::endl;
    // pop
    Parser::vol_type vol;
    auto token = parser.token_stack.top();
    vol.type = VOL_IS_NUM_VALUE;
    vol.ivol = 2;
    std::cout << "-------------- " << vol.ivol << std::endl;
    parser.token_stack.pop();
    parser.status_stack.pop();
    parser.vol_stack.push(vol);
}
// value_type -> int | float | char etc...
void Translater::action_VT(Parser& parser)
{

    std::cout << "VT -> Translater" << std::endl;
    // pop
    Parser::vol_type vol;
    auto token = parser.token_stack.top();
    vol.type = VOL_IS_VALUE_TYPE;
    vol.ivol = token.get_token();
    parser.token_stack.pop();
    parser.status_stack.pop();
    parser.vol_stack.push(vol);
}
void Translater::action_value_declare(Parser& parser)
{
    std::cout << "value_declare -> Translater" << std::endl;
    // pop
    for (size_t i = 0; i < action_production.size(); ++i) {
        parser.token_stack.pop();
        parser.status_stack.pop();
    }
}

void Translater::action_value_define(Parser& parser)
{
    std::cout << "value_define -> Translater" << std::endl;
    // pop
    for (size_t i = 0; i < action_production.size(); ++i) {
        parser.token_stack.pop();
        parser.status_stack.pop();
    }
}

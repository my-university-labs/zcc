/* author: dongchangzhang */
/* time: 2017年04月20日 星期四 18时27分33秒 */

#include "translate.h"
#include "parser.h"
#include <iostream>
#include <sstream>

void Translater::action_run(Parser& parser, std::string& action, std::string& which, size_t index)
{
    action_which = which;
    action_index = index;
    action_production = parser.grammar.get_production(which, index);
    if (action == "action_ARRAY") {
        action_ARRAY(parser);
    } else if (action == "action_ATIMES") {
        action_ATIMES(parser);
    } else if (action == "action_CALC") {
        action_CALC(parser);
    } else if (action == "action_ID") {
        action_ID(parser);
    } else if (action == "action_POP") {
        action_POP(parser);
    } else if (action == "action_SWAP") {
        action_SWAP(parser);
    } else if (action == "action_VE") {
        action_VE(parser);
    } else if (action == "action_VT") {
        action_VT(parser);
    } else if (action == "action_value_declare") {
        action_value_declare(parser);
    } else if (action == "action_value_declare1") {
        action_value_declare1(parser);
    } else if (action == "action_value_define") {
        action_value_define(parser);
    } else if (action == "action_value_define1") {
        action_value_define1(parser);
    } else {
        // std::cout << "ELSE -> Translater" << std::endl;
        // pop
        pop_all(parser);
    }
}

template <typename T0, typename T1, typename T2>
size_t Translater::generate_code(T0 op, T1& value1, T2& value2, Parser& parser)
{
    if (value1.type == VOL_IS_TMP && value2.type == VOL_IS_TMP)
        return cmanager.generate_code(op, value1.index, value2.index, parser.smanager);
    else if (value1.type == VOL_IS_TMP && value2.type != VOL_IS_TMP)
        return cmanager.generate_code(op, value1.index, value2.addr, parser.smanager);
    else if (value1.type != VOL_IS_TMP && value2.type == VOL_IS_TMP)
        return cmanager.generate_code(op, value1.addr, value2.index, parser.smanager);
    else if (value1.type != VOL_IS_TMP && value2.type != VOL_IS_TMP)
        return cmanager.generate_code(op, value1.addr, value2.addr, parser.smanager);
    else
        return 0;
}

template <typename T1, typename T2, typename T3>
T1 Translater::calcu_exp(T1& value1, T2& value2, T3& op)
{
    Parser::vol_type r = value1;
    if (value1.type == value2.type && value1.type == VOL_IS_NUM_VALUE)
        r.ivol += value2.ivol;
    return r;
}

void Translater::pop_all(Parser& parser)
{
    for (size_t i = 0; i < action_production.size(); ++i) {
        parser.token_stack.pop();
        parser.status_stack.pop();
    }
}
void Translater::action_ARRAY(Parser& parser)
{
    pop_all(parser);
    auto times = parser.vol_stack.top();
    parser.vol_stack.pop();

    auto id = parser.vol_stack.top();
    parser.vol_stack.pop();

    // auto type = parser.vol_stack.top();

    std::cout << "insert into symbol table: array name -> " << id.svol << " times is: ";
    for (auto t : times.array_times) {
        parser.smanager.print_addr_info(t);
        std::cout << " ";
    }
    std::cout << std::endl;
}
void Translater::action_ATIMES(Parser& parser)
{
    pop_all(parser);
    auto times = parser.vol_stack.top();
    parser.vol_stack.pop();
    if (parser.vol_stack.top().type == VOL_IS_ARRAY) {
        parser.vol_stack.top().array_times.push_back(times.addr);
    } else {
        Parser::vol_type vol;
        vol.type = VOL_IS_ARRAY;
        vol.array_times.push_back(times.addr);
        parser.vol_stack.push(vol);
    }
}

void Translater::action_CALC(Parser& parser)
{
    // std::cout << "CALC -> Translater" << std::endl;

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

    auto r = generate_code(op.get_token(), value1, value2, parser);
    cmanager.print_code(r, parser.smanager);

    Parser::vol_type vol;
    vol.index = r;
    vol.type = VOL_IS_TMP;
    parser.vol_stack.push(vol);
}
void Translater::action_ID(Parser& parser)
{

    // std::cout << "ID -> Translater" << std::endl;
    // pop
    Parser::vol_type vol;
    auto token = parser.token_stack.top();
    vol.type = VOL_IS_ID;
    vol.addr = token.get_addr();
    parser.token_stack.pop();
    parser.status_stack.pop();
    parser.vol_stack.push(vol);
}

void Translater::action_POP(Parser& parser)
{
    parser.vol_stack.pop();
    for (size_t i = 0; i < action_production.size(); ++i) {
        parser.token_stack.pop();
        parser.status_stack.pop();
    }
}
void Translater::action_SWAP(Parser& parser)
{

    // std::cout << "SWAP -> Translater" << std::endl;
    // pop
    parser.token_stack.pop();
    parser.status_stack.pop();
}
void Translater::action_VE(Parser& parser)
{
    // std::cout << "VE -> Translater" << std::endl;
    // pop
    Parser::vol_type vol;
    auto token = parser.token_stack.top();
    vol.type = VOL_IS_NUM_VALUE;
    vol.addr = token.get_addr();
    parser.token_stack.pop();
    parser.status_stack.pop();
    parser.vol_stack.push(vol);
}
// value_type -> int | float | char etc...
void Translater::action_VT(Parser& parser)
{

    // std::cout << "VT -> Translater" << std::endl;
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
    // std::cout << "value_declare -> Translater" << std::endl;
    // pop
    auto id = parser.vol_stack.top();
    parser.token_stack.pop();
    parser.status_stack.pop();
    parser.vol_stack.pop();
    auto type = parser.vol_stack.top();
    std::cout << "insert into symbol table: " << get_token_info(type.type) << " " << id.svol << std::endl;
}

void Translater::action_value_declare1(Parser& parser)
{
    action_value_declare(parser);
    parser.token_stack.pop();
    parser.status_stack.pop();
    parser.token_stack.pop();
    parser.status_stack.pop();
}
void Translater::action_value_define(Parser& parser)
{
    // std::cout << "value_define -> Translater" << std::endl;
    // pop
    auto vol = parser.vol_stack.top();
    parser.token_stack.pop();
    parser.status_stack.pop();
    parser.vol_stack.pop();

    parser.token_stack.pop();
    parser.status_stack.pop();

    auto id = parser.vol_stack.top();
    parser.token_stack.pop();
    parser.status_stack.pop();
    parser.vol_stack.pop();

    auto type = parser.vol_stack.top();

    std::cout << "insert into symbol table: " << get_token_info(type.type) << " " << id.svol << " " << vol.index << std::endl;
}
void Translater::action_value_define1(Parser& parser)
{
    action_value_define(parser);
    parser.token_stack.pop();
    parser.status_stack.pop();
    parser.token_stack.pop();
    parser.status_stack.pop();
}
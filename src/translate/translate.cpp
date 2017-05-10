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
    if (action == "action_AND") {
        action_AND(parser);
    } else if (action == "action_ARRAY") {
        action_ARRAY(parser);
    } else if (action == "action_ARRAY_ADDR") {
        action_ARRAY_ADDR(parser);
    } else if (action == "action_ARRAY_ASSIGN") {
        action_ARRAY_ASSIGN(parser);
    } else if (action == "action_ASSIGN") {
        action_ASSIGN(parser);
    } else if (action == "action_ATIMES") {
        action_ATIMES(parser);
    } else if (action == "action_BOOL1") {
        action_BOOL1(parser);
    } else if (action == "action_BOOL2") {
        action_BOOL2(parser);
    } else if (action == "action_CALC") {
        action_CALC(parser);
    } else if (action == "action_ELSE") {
        action_ELSE(parser);
    } else if (action == "action_ELSEIF") {
        action_ELSEIF(parser);
    } else if (action == "action_FOR") {
        action_FOR(parser);
    } else if (action == "action_ID") {
        action_ID(parser);
    } else if (action == "action_IF") {
        action_IF(parser);
    } else if (action == "action_IF_B") {
        action_IF_B(parser);
    } else if (action == "action_OR") {
        action_OR(parser);
    } else if (action == "action_POP") {
        action_POP(parser);
    } else if (action == "action_SWAP") {
        action_SWAP(parser);
    } else if (action == "action_VE") {
        action_VE(parser);
    } else if (action == "action_VT") {
        action_VT(parser);
    } else if (action == "action_WHILE") {
        action_WHILE(parser);
    } else if (action == "action_value_declare") {
        action_value_declare(parser);
    } else if (action == "action_value_declare1") {
        action_value_declare1(parser);
    } else if (action == "action_value_define") {
        action_value_define(parser);
    } else if (action == "action_value_define1") {
        action_value_define1(parser);
    } else if (action == "action_M_FLAG") {
        action_M_FLAG(parser);
    } else if (action == "action_N_FLAG") {
        action_N_FLAG(parser);
    } else if (action == "action_M1_FLAG") {
        action_M1_FLAG(parser);
    } else if (action == "action_S_FLAG") {
        action_M2_FLAG(parser);
    } else if (action == "action_S_FLAG") {
        action_S_FLAG(parser);
    } else if (action == "action_SS_FLAG") {
        action_SS_FLAG(parser);
    } else if (action == "action_F1_FLAG") {
        action_F1_FLAG(parser);
    } else if (action == "action_F2_FLAG") {
        action_F2_FLAG(parser);
    } else if (action == "action_F3_FLAG") {
        action_F3_FLAG(parser);
    } else {
        pop_all(parser);
    }
}

void Translater::pop_all(Parser& parser)
{
    for (size_t i = 0; i < action_production.size(); ++i) {
        parser.token_stack.pop();
        parser.status_stack.pop();
    }
}

size_t Translater::gen_3_addr(Parser& parser, int flag, addr_type& addr1, addr_type& addr2)
{
    size_t next = code_manager.line_nums_now();
    addr_type jump_true = parser.smanager.install_value((int)next + 2);
    size_t r;
    if (!gen_to_tmp)
        r = code_manager.generate_code(flag, addr1, addr2, jump_true, parser.smanager);
    else
        r = code_manager.generate_tmp_code(flag, addr1, addr2, jump_true, parser.smanager);
    code_manager.print_code(r, parser.smanager);
    backfill_true.push(jump_true);
    return r;
}

size_t Translater::gen_1_addr(Parser& parser, int flag)
{
    addr_type jump_false = parser.smanager.install_value(0);
    size_t r;
    if (!gen_to_tmp)
        r = code_manager.generate_code(flag, jump_false, parser.smanager);
    else
        r = code_manager.generate_tmp_code(flag, jump_false, parser.smanager);
    code_manager.print_code(r, parser.smanager);
    backfill_false.push(jump_false);
    return r;
}

void Translater::action_AND(Parser& parser)
{
    pop_all(parser);
    auto value1 = parser.vol_stack.top();
    parser.vol_stack.pop();
    auto value2 = parser.vol_stack.top();
    parser.vol_stack.pop();

    auto r = gen_3_addr(parser, AND, value1.addr, value2.addr);

    gen_1_addr(parser, GOTO);

    Parser::vol_type vol;
    vol.index = r;
    vol.addr = code_manager.get_tmp_addr(r);
    parser.vol_stack.push(vol);
}
void Translater::action_ARRAY(Parser& parser)
{
    pop_all(parser);
    auto times = parser.vol_stack.top();
    parser.vol_stack.pop();

    auto id = parser.vol_stack.top();
    parser.vol_stack.pop();

    auto type = parser.vol_stack.top();

    std::vector<int> tmp;
    for (auto t : times.array_times) {
        tmp.push_back(parser.smanager.get_int(t));
    }
    parser.smanager.declare_array(type.ivol, id.addr, tmp);
}

void Translater::action_ARRAY_ADDR(Parser& parser)
{

    action_SWAP(parser);
    auto times = parser.vol_stack.top();
    parser.vol_stack.pop();

    auto id = parser.vol_stack.top();
    parser.vol_stack.pop();

    std::vector<int> tmp;
    for (auto t : times.array_times) {
        tmp.push_back(parser.smanager.get_int(t));
    }
    Parser::vol_type vol;
    vol.type = VOL_IS_ARRAY_ELEMENT;
    vol.addr = parser.smanager.get_array_element_addr(id.addr, tmp);

    parser.vol_stack.push(vol);
}
void Translater::action_ARRAY_ASSIGN(Parser& parser)
{
    pop_all(parser);
    auto vol = parser.vol_stack.top();
    parser.vol_stack.pop();
    auto times = parser.vol_stack.top();
    parser.vol_stack.pop();

    auto id = parser.vol_stack.top();
    parser.vol_stack.pop();

    std::vector<int> tmp;
    for (auto t : times.array_times) {
        tmp.push_back(parser.smanager.get_int(t));
    }
    Parser::vol_type vol1;
    vol1.type = VOL_IS_ARRAY_ELEMENT;
    vol1.addr = parser.smanager.get_array_element_addr(id.addr, tmp);

    parser.vol_stack.push(vol1);

    // parser.smanager.array_assignment(vol1.addr, vol.addr);

    auto r = code_manager.generate_code(ARRAY_ASSIGN, vol1.addr, vol.addr, parser.smanager);
    code_manager.print_code(r, parser.smanager);
}

void Translater::action_ASSIGN(Parser& parser)
{
    pop_all(parser);
    auto vol = parser.vol_stack.top();
    parser.vol_stack.pop();
    auto id = parser.vol_stack.top();
    parser.vol_stack.pop();

    auto r = code_manager.generate_code(ASSIGN, id.addr, vol.addr, parser.smanager);

    code_manager.print_code(r, parser.smanager);
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
void Translater::action_BOOL1(Parser& parser)
{
    pop_all(parser);
    auto value = parser.vol_stack.top();
    parser.vol_stack.pop();
    value.type = VOL_IS_BOOL;
    value.addr = parser.smanager.conver_to_bool(value.addr);
    parser.vol_stack.push(value);
}
void Translater::action_BOOL2(Parser& parser)
{
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

    auto r = gen_3_addr(parser, AND, value1.addr, value2.addr);

    gen_1_addr(parser, GOTO);

    Parser::vol_type vol;
    vol.index = r;
    vol.addr = code_manager.get_tmp_addr(r);
    parser.vol_stack.push(vol);
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

    auto r = code_manager.generate_code(op.get_token(), value1.addr, value2.addr, parser.smanager);
    code_manager.print_code(r, parser.smanager);

    Parser::vol_type vol;
    vol.index = r;
    vol.addr = code_manager.get_tmp_addr(r);
    parser.vol_stack.push(vol);

    // print_code(r, vol, op, value1, value2, parser);
}
void Translater::action_ELSE(Parser& parser)
{
    pop_all(parser);
}
void Translater::action_ELSEIF(Parser& parser)
{
    pop_all(parser);
    // jump out if-elseif-else
    // need to be backfilled
    addr_type jump_false = parser.smanager.install_value(0);
    auto r1 = code_manager.generate_code(GOTO, jump_false, parser.smanager);
    code_manager.print_code(r1, parser.smanager);
    // backfill if-false-jump
    size_t next = code_manager.line_nums_now();
    for (int i = 0; i < bool_nums.top(); ++i) {
        auto addr = backfill_false.top();
        parser.smanager.value_assignment(addr, (int)next);
        backfill_false.pop();
    }
    bool_nums.pop();
    // push it into backfilll stack
    backfill_false.push(jump_false);
}
void Translater::action_FOR(Parser& parser)
{
    pop_all(parser);
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
void Translater::action_IF(Parser& parser)
{
    pop_all(parser);
    // jump out if-elseif-else
    // need to be backfilled
    addr_type jump_false = parser.smanager.install_value(0);
    auto r1 = code_manager.generate_code(GOTO, jump_false, parser.smanager);
    code_manager.print_code(r1, parser.smanager);
    // backfill if-false-jump
    size_t next = code_manager.line_nums_now();
    for (int i = 0; i < bool_nums.top(); ++i) {
        std::cout << "POP1" << std::endl;
        auto addr = backfill_false.top();
        parser.smanager.value_assignment(addr, (int)next);
        backfill_false.pop();
    }
    bool_nums.pop();
    backfill_false.push(jump_false);
}
void Translater::action_IF_B(Parser& parser)
{
    pop_all(parser);
    std::cout << bool_nums.top() << " " << backfill_false.size() << std::endl;
    size_t next = code_manager.line_nums_now();
    for (int i = 0; i < bool_nums.top(); ++i) {
        std::cout << "POP2" << std::endl;
        auto addr = backfill_false.top();
        parser.smanager.value_assignment(addr, (int)next);
        backfill_false.pop();
    }
    bool_nums.pop();
}
void Translater::action_OR(Parser& parser)
{
    pop_all(parser);
    auto value1 = parser.vol_stack.top();
    parser.vol_stack.pop();
    auto value2 = parser.vol_stack.top();
    parser.vol_stack.pop();

    size_t next = code_manager.line_nums_now();
    addr_type jump_true = parser.smanager.install_value((int)next + 2);
    auto r = code_manager.generate_code(OR, value1.addr, value2.addr, jump_true, parser.smanager);
    code_manager.print_code(r, parser.smanager);

    backfill_true.push(jump_true);

    addr_type jump_false = parser.smanager.install_value(0);
    auto r1 = code_manager.generate_code(GOTO, jump_false, parser.smanager);
    code_manager.print_code(r1, parser.smanager);

    backfill_false.push(jump_false);

    Parser::vol_type vol;
    vol.index = r;
    vol.addr = code_manager.get_tmp_addr(r);
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
void Translater::action_WHILE(Parser& parser)
{
    pop_all(parser);
    // gencode to back up the start of while
    addr_type jump_back = parser.smanager.install_value(0);
    size_t back_nu = line_to_jump.top();
    line_to_jump.pop();
    parser.smanager.value_assignment(jump_back, (int)back_nu);
    // gencode
    auto r1 = code_manager.generate_code(GOTO, jump_back, parser.smanager);
    code_manager.print_code(r1, parser.smanager);
    // the first line out of while statement, do backfill
    size_t next = code_manager.line_nums_now();
    for (int i = 0; i < bool_nums.top(); ++i) {
        auto addr = backfill_false.top();
        parser.smanager.value_assignment(addr, (int)next);
        backfill_false.pop();
    }
    bool_nums.pop();
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
    parser.smanager.declare_define_variable(type.ivol, id.addr);
    // std::cout << "insert into symbol table: " << get_token_info(type.type) << " " << id.svol << std::endl;
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
    if (vol.type == VOL_IS_TMP)
        vol.addr = code_manager.get_tmp_addr(vol.index);

    // parser.smanager.declare_define_variable(type.ivol, id.addr, vol.addr);
    parser.smanager.declare_define_variable(type.ivol, id.addr);
    auto r = code_manager.generate_code(ASSIGN, id.addr, vol.addr, parser.smanager);
    code_manager.print_code(r, parser.smanager);

    // std::cout << "insert into symbol table: " << get_token_info(type.type) << " " << id.svol << " " << vol.index << std::endl;
}
void Translater::action_value_define1(Parser& parser)
{
    action_value_define(parser);
    parser.token_stack.pop();
    parser.status_stack.pop();
    parser.token_stack.pop();
    parser.status_stack.pop();
}

void Translater::action_M_FLAG(Parser& parser)
{
    pop_all(parser);
    size_t next = code_manager.line_nums_now();
    // line_to_jump.push(next);
    auto addr = backfill_true.top();
    parser.smanager.value_assignment(addr, (int)next);
}
void Translater::action_N_FLAG(Parser& parser)
{
    pop_all(parser);
    // line_to_jump.push(next);
}

void Translater::action_M1_FLAG(Parser& parser)
{
    pop_all(parser);
    // come into a new while
    bool_nums.push(0);
    size_t next = code_manager.line_nums_now();
    line_to_jump.push(next);
}
void Translater::action_M2_FLAG(Parser& parser)
{
    pop_all(parser);
    // backfill true-jump
    size_t next = code_manager.line_nums_now();
    auto addr = backfill_true.top();
    backfill_true.pop();
    parser.smanager.value_assignment(addr, (int)next);
}
void Translater::action_S_FLAG(Parser& parser)
{
    // come into if
    pop_all(parser);
    bool_nums.top() += 1;
    bool_nums.push(0);
}
void Translater::action_SS_FLAG(Parser& parser)
{
    // come into if
    pop_all(parser);
    bool_nums.push(1);
    bool_nums.push(0);
}
void Translater::action_F1_FLAG(Parser& parser)
{
    // come into for
    pop_all(parser);
    // record how many bool-false need tobe backfill
    bool_nums.push(0);
    gen_to_tmp = true;
}
void Translater::action_F2_FLAG(Parser& parser)
{
    // gen goto
    gen_to_tmp = false;
    action_M1_FLAG(parser);
}
void Translater::action_F3_FLAG(Parser& parser)
{
    // mege tmp code to code
    action_M1_FLAG(parser);
}
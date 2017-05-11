/* author: dongchangzhang */
/* time: 2017年04月20日 星期四 18时29分12秒 */

#ifndef SRC_TRANSLATE_TRANSLATE_H
#define SRC_TRANSLATE_TRANSLATE_H

#include "code.h"
#include "codemanager.h"
#include "symboltable.h"
#include "token.h"
#include <stack>
#include <string>
#include <vector>

class Parser;
class Translater {
public:
    Translater()
        : timer(0)
    {
    }

    void action_run(Parser& parser, std::string& action, std::string& which, size_t index);
    void gencode(SymbolTableManager& stmg) { code_manager.gen_all_code(stmg); }
    std::vector<Code> get_codes() { return code_manager.get_codes(); }

private:
    size_t timer;
    // action -> tokens
    // action
    size_t action_index;
    // tokens
    std::string action_which;
    std::vector<Token> action_production;
    // code manager
    CodeManager code_manager;
    // backfill stack
    std::stack<addr_type> backfill_true;
    std::stack<addr_type> backfill_false;
    // save line nums
    std::stack<size_t> line_to_jump;
    // how many addr need to be backfilled this time
    std::stack<int> bool_nums;

    size_t timer_increase() { return ++timer; }

    bool gen_to_tmp = false;

    void pop_all(Parser& parser);

    void bool_if(Parser& parser);

    size_t gen_3_addr(Parser& parser, int flag, addr_type& addr1, addr_type& addr2);

    size_t gen_1_addr(Parser& parser, int flag);

    void action_AND(Parser& parser);

    void action_ARRAY(Parser& parser);

    void action_ARRAY_ADDR(Parser& parser);

    void action_ARRAY_ASSIGN(Parser& parser);

    void action_ASSIGN(Parser& parser);

    void action_ATIMES(Parser& parser);

    void action_BOOL1(Parser& parser);

    void action_BOOL2(Parser& parser);

    void action_CALC(Parser& parser);

    void action_ELSE(Parser& parser);

    void action_ELSEIF(Parser& parser);

    void action_FOR(Parser& parser);

    void action_ID(Parser& parser);

    void action_IF(Parser& parser);

    void action_IF_B(Parser& parser);

    void action_OR(Parser& parser);

    void action_POP(Parser& parser);

    void action_SWAP(Parser& parser);

    void action_VE(Parser& parser);

    void action_VT(Parser& parser);

    void action_WHILE(Parser& parser);

    void action_value_declare(Parser& parser);
    void action_value_declare1(Parser& parser);

    void action_value_define(Parser& parser);
    void action_value_define1(Parser& parser);

    void action_array_declare(Parser& parser);
    void action_array_declare1(Parser& parser);

    // M
    void action_M_FLAG(Parser& parser);
    // N
    void action_N_FLAG(Parser& parser);
    // M1
    void action_M1_FLAG(Parser& parser);
    // M2
    void action_M2_FLAG(Parser& parser);
    // S elseif begin
    void action_S_FLAG(Parser& parser);
    // SS if begin
    void action_SS_FLAG(Parser& parser);
    // F1
    void action_F1_FLAG(Parser& parser);
    // F2
    void action_F2_FLAG(Parser& parser);
    // F3
    void action_F3_FLAG(Parser& parser);
};
#endif

/* author: dongchangzhang */
/* time: 2017年04月20日 星期四 18时29分12秒 */

#ifndef SRC_TRANSLATE_TRANSLATE_H
#define SRC_TRANSLATE_TRANSLATE_H

#include "codemanager.h"
#include "token.h"
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

private:
    size_t timer;
    size_t action_index;
    std::string action_which;
    std::vector<Token> action_production;

    CodeManager cmanager;

    size_t timer_increase() { return ++timer; }

    void pop_all(Parser& parser);

    void bool_if(Parser& parser);

    void action_ARRAY(Parser& parser);

    void action_ARRAY_ADDR(Parser& parser);

    void action_ARRAY_ASSIGN(Parser& parser);

    void action_ASSIGN(Parser& parser);

    void action_ATIMES(Parser& parser);

    void action_BOOL1(Parser& parser);

    void action_BOOL2(Parser& parser);

    void action_CALC(Parser& parser);

    void action_ID(Parser& parser);

    void action_POP(Parser& parser);

    void action_SWAP(Parser& parser);

    void action_VE(Parser& parser);

    void action_VT(Parser& parser);

    void action_value_declare(Parser& parser);
    void action_value_declare1(Parser& parser);

    void action_value_define(Parser& parser);
    void action_value_define1(Parser& parser);

    void action_array_declare(Parser& parser);
    void action_array_declare1(Parser& parser);
};
#endif

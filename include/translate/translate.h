/* author: dongchangzhang */
/* time: 2017年04月20日 星期四 18时29分12秒 */

#ifndef SRC_TRANSLATE_TRANSLATE_H
#define SRC_TRANSLATE_TRANSLATE_H

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

    size_t timer_increase() { return ++timer; }

    template <typename T1, typename T2, typename T3>
    void generate_code(T1& value1, T2& value2, T3& op);

    template <typename T1, typename T2, typename T3>
    T1 calcu_exp(T1& value1, T2& value2, T3& op);

    void action_CALC(Parser& parser);

    void action_ID(Parser& parser);

    void action_SWAP(Parser& parser);

    void action_VE(Parser& parser);

    void action_VT(Parser& parser);

    void action_value_declare(Parser& parser);

    void action_value_define(Parser& parser);

    void action_array_declare(Parser& parser);
};
#endif

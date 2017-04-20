/* author: dongchangzhang */
/* time: 2017年04月20日 星期四 18时27分33秒 */
#include "translate.h"
#include <iostream>

void action_VT()
{
    ;
}
void action_value_declare()
{
    std::cout << "ACTION_VALUE_DECLARE" << std::endl;
}

void action_value_define()
{
    std::cout << "ACTION_VALUE_DEFINE" << std::endl;
}

void action_run(std::string& action)
{
    if (action == "action_VT") {
        action_VT();
    } else if (action == "action_value_declare") {
        action_value_declare();
    } else if (action == "action_value_define") {
        action_value_define();
    }
}
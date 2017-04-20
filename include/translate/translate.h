/* author: dongchangzhang */
/* time: 2017年04月20日 星期四 18时29分12秒 */

#ifndef SRC_TRANSLATE_TRANSLATE_H
#define SRC_TRANSLATE_TRANSLATE_H

#include "token.h"
#include <string>
#include <vector>

void action_VT();

void action_value_declare();

void action_value_define();

void action_array_declare();

void action_run(std::string& action);

#endif

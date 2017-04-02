/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 10:54:34 PM CST */

#include "grammar_tool.h"
#include "unstd.h"

#include <iostream>
#include <algorithm>

Status GrammarDealer::closure(Item &item)
{

    Status s;
    return s;
}

Status GrammarDealer::go(size_t status, Token &token) 
{
    Status s;
    return s;
}

std::vector<int> first(const std::vector<Token> &left)
{
    std::vector<int> r;
    bool changed = false;
    bool have_null = false;
    if (!left[0].is_state_token()) {
        r.push_back(left[0].get_token())
    }
    else {
        size_t i = 0;
        std::vector<std::vector<Token>> p;
        while (i < left.size()) {
            have_null = false;
            p = grammar.get_production(token[i]);
            for (auto &vt : p){
                if (vt.size() == 1 && vt.at(0).is_null_state()) {
                    have_null = true;
                }
            } 
        }
    }
    if (first_saver.find(left) == first_saver.end()) {
        first_saver[left] = r;
    }
    return r;
}

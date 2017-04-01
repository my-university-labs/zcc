/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 11:51:07 PM CST */
#ifndef TOOLS_GRAMMAR_DFA_H
#define TOOLS_GRAMMAR_DFA_H

#include "item.h"
#include "status.h"
#include "token.h"
#include <map>
#include <vector>

Class DFA {
    public:
        DFA();
    private:
        std::vector<Status> graph;
        std::map<size_t, std::map<Token, size_t>> relation;
};
#endif

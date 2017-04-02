/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 10:54:52 PM CST */

#ifndef TOOLS_GRAMMAR_TOOL_H
#define TOOLS_GRAMMAR_TOOL_H

#include "token.h"
#include "item.h"
#include "status.h"
#include "grammar.h"
#include <string>
#include <vector>

class GrammarDealer {
public:
    GrammarDealer(std::string grammarf): grammar(grammarf) { grammar.check_grammar(); }


    void run();
    
private:
    Status closure(Item &item);

    Status go();
    
    std::vector<int> first(const std::vector<Token> &left);

    Grammar grammar;

};
#endif

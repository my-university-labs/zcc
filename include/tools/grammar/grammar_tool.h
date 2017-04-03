/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 10:54:52 PM CST */

#ifndef TOOLS_GRAMMAR_TOOL_H
#define TOOLS_GRAMMAR_TOOL_H

#include "grammar.h"
#include "item.h"
#include "status.h"
#include "token.h"

#include <map>
#include <string>
#include <vector>

class GrammarDealer {
public:
    GrammarDealer(std::string grammarf)
        : grammar(grammarf)
    {
        grammar.check_grammar();
    }

    void run();

private:
    Status closure(Item& item);

    Status go(size_t status, Token& token);

    std::vector<int> first(const std::vector<Token>& left);

    Grammar grammar;

    std::map<std::vector<Token>, std::vector<int> > first_saver;
};
#endif

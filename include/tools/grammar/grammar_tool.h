/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 10:54:52 PM CST */

#ifndef TOOLS_GRAMMAR_TOOL_H
#define TOOLS_GRAMMAR_TOOL_H

#include "dfa.h"
#include "grammar.h"
#include "item.h"
#include "parsing_table.h"
#include "status.h"
#include "token.h"

#include <map>
#include <string>
#include <unordered_set>
#include <vector>

class GrammarDealer {
public:
    GrammarDealer(std::string grammarf)
        : grammar(grammarf)
    {
        // grammar.check_grammar();
    }

    void run();

    void test_firstX(std::string X);

    void test_first(std::string line);

private:
    bool closure_debug = false;
    // 闭包
    Status closure(Status& status);
    // go function
    Status go(const Status& status, const Token& token);
    // first(X1X2X3X4...)
    std::unordered_set<int> first(const std::vector<Token>& left);
    // first(X)
    std::unordered_set<int> firstX(const Token& token);

    size_t create_dfa();

    void create_parsing_table();
    // save grammar
    Grammar grammar;
    // DFA
    DFA dfa;
    // parsing table (goto && action)
    ParsingTable parsing_table;
};

#endif

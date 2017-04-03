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

    void test_first(std::string input);

private:
    // 闭包
    Status closure(Item& item);
    // go function
    Status go(size_t status, Token& token);
    // first(X1X2X3X4...)
    std::unordered_set<int> first(const std::vector<Token>& left);
    // first(X)
    std::unordered_set<int> firstX(const Token& token);
    // save grammar
    Grammar grammar;
    // save first
    std::map<std::vector<Token>, std::unordered_set<int> > first_saver;
};

#endif

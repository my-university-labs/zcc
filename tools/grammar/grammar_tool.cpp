/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 10:54:34 PM CST */

#include "grammar_tool.h"
#include "unstd.h"

#include <algorithm>
#include <iostream>
// predeclaration
static bool merge_set_ignore_null(std::unordered_set<int>& set1,
    const std::unordered_set<int>& set2);

void GrammarDealer::test_firstX(std::string X)
{
    Token token(X);
    auto r = firstX(token);
    std::cout << "ANS: " << std::endl;
    for (auto i : r) {
        std::cout << i << std::endl;
    }
}

Status GrammarDealer::closure(Item& item)
{

    Status s;
    return s;
}

Status GrammarDealer::go(size_t status, Token& token)
{
    Status s;
    return s;
}

std::unordered_set<int> GrammarDealer::first(const std::vector<Token>& left)
{
    size_t index = 0;
    bool have_null = false;
    std::unordered_set<int> Xsset;
    Xsset = firstX(left.at(index++));
    have_null = Xsset.find(NULL_STATE) == Xsset.end() ? false : true;
    Xsset.erase(NULL_STATE);
    while (have_null && index < left.size()) {
        auto s = firstX(left.at(index++));
        have_null = merge_set_ignore_null(Xsset, s);
    }
    if (have_null && index == left.size())
        Xsset.insert(NULL_STATE);
    return Xsset;
}
std::unordered_set<int> GrammarDealer::firstX(const Token& token)
{
    std::unordered_set<int> Xset;
    Xset.clear();
    if (!token.is_state_token() && !token.is_null_token()) {
        Xset.insert(token.get_token());
    } else {
        // production1、 production2 ..., saved by v<v<token>>
        auto ps = grammar.get_production(token);
        // terminal symbol
        for (auto p : ps) {
            // null token
            if (p.size() == 1 && p.at(0).is_null_token()) {
                Xset.insert(NULL_STATE);
            } else if (p.size() > 0 && !p.at(0).is_state_token()) {
                Xset.insert(p.at(0).get_token());
            }
        }
        // none terminal symbol
        bool have_null = false;
        //  while (!changed) {
        for (auto& p : ps) { // every production
            for (auto& t : p) { // every token of every production
                have_null = false;
                if (t.is_state_token()) {
                    auto s = firstX(t);
                    have_null = merge_set_ignore_null(Xset, s);
                    // don't have null state ->  break
                    if (!have_null) {
                        break;
                    }
                    // have null look next
                } else if (!t.is_null_token()) {
                    Xset.insert(t.get_token());
                    break;
                }
            }
            if (have_null) {
                Xset.insert(NULL_STATE);
            }
        }
        // }
    }
    return Xset;
}

static bool merge_set_ignore_null(std::unordered_set<int>& set1,
    const std::unordered_set<int>& set2)
{
    bool have_null = false;
    for (auto s : set2) {
        if (s == NULL_STATE)
            have_null = true;
        else
            set1.insert(s);
    }
    return have_null;
}
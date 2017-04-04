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
    Item item("E", 0, END_STATE, 2);
}

Status GrammarDealer::closure(Status& status)
{
    size_t last_size = 0;

    while (last_size != status.size()) {
        last_size = status.size();
        // items in status -> unordered_set
        auto content = status.get_content();
        for (auto i : content) {
            if (!i.is_end() && i.next_is_state(grammar)) {
                // next state token X1
                Token token = i.after_decimal(grammar);
                // v<token> X1X2X3X4
                auto for_terminal_symbols = i.for_first(grammar);
                //terminal symbol -> unordered_set<int>
                auto end_symbols = first(for_terminal_symbols);
                // all productions v<v<token>>
                auto ps = grammar.get_production(token);
                for (size_t loc = 0; loc < ps.size(); ++loc) {
                    for (auto end_symbol : end_symbols) {
                        // which index end_symbol productionsize
                        Item new_item(token.get_state(), loc, end_symbol, ps.at(loc).size());
                        status.add_item(new_item);
                    }
                }
            }
        }
    }
    return status;
}

Status GrammarDealer::go(const Status& status, const Token& token)
{
    Status new_status;
    auto content = status.get_content();
    for (auto item : content) {
        if (!item.is_end() && item.after_decimal(grammar) == token) {
            item.move_decimal();
            new_status.add_item(item);
        }
    }
    return closure(new_status);
}

size_t GrammarDealer::create_dfa()
{
    Item start_item(grammar.get_start_state(), grammar.get_start_index(),
        END_STATE, grammar.get_start_size());
    Status start_status;
    start_status.add_item(start_item);
    // I0
    auto start = closure(start_status);
    // save it to dfa as first state
    size_t start_location = dfa.add_start_status(start);
    // start to find I1 I2 ...
    for (size_t index = dfa.get_work_index(); !dfa.no_status_left();
         index = dfa.move_next()) {
        std::unordered_set<Token> check_repeat;
        Status work_status = dfa.get_status(index);
        auto items = work_status.get_content();
        for (auto item : items) {
            Token adtoken = item.after_decimal(grammar);
            if (check_repeat.find(adtoken) != check_repeat.end()) {
                check_repeat.insert(adtoken);
                auto new_status = go(work_status, adtoken);
                dfa.add_status(work_status, adtoken, new_status);
            }
        }
    }
    return start_location;
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
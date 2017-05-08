/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 10:54:34 PM CST */

#include "grammar_tool.h"
#include "unstd.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>

// predeclaration
static bool merge_set_ignore_null(std::unordered_set<int>& set1,
    const std::unordered_set<int>& set2);

void GrammarDealer::run()
{
    std::cout << "# CREATE DFA #" << std::endl;
    create_dfa();
    std::cout << "# CREATE PARSING TABLE #" << std::endl;
    create_parsing_table();
    std::cout << "# SAVE PARSING TABLE INFORMATION TO FILE: "
              << PARSING_TABLE_FILE_NAME << std::endl;
    parsing_table.save_table_to_file();
    std::cout << "$ ALL DONE" << std::endl;
}

void GrammarDealer::test_first(std::string line)
{
    int code;
    std::string word;
    std::istringstream is(line);
    std::vector<Token> target;
    while (is >> word) {
        if (word == "identity") {
            target.push_back(Token(ID, word));
        } else if ((code = get_code(word)) == ID)
            target.push_back(Token(word));
        else
            target.push_back(Token(code, word));
    }
    auto r = first(target);
    for (auto i : r) {
        std::cout << i << std::endl;
    }
}
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
                        Item new_item(token.get_state(),
                            loc, end_symbol, ps.at(loc).size());
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
    closure_debug = true;
    for (size_t index = dfa.get_work_index(); !dfa.no_status_left();
         index = dfa.move_next()) {
        std::unordered_set<Token> check_repeat;
        Status work_status = dfa.get_status(index);
        auto items = work_status.get_content();
        for (auto item : items) {
            if (item.is_end())
                continue;
            Token adtoken = item.after_decimal(grammar);
            if (check_repeat.find(adtoken) == check_repeat.end()) {
                check_repeat.insert(adtoken);
                auto new_status = go(work_status, adtoken);

                dfa.add_status(work_status, adtoken, new_status);
            }
        }
    }
    return start_location;
}

void GrammarDealer::create_parsing_table()
{
    // move work status to first status
    dfa.clear_work_index();
    // for all status I0 I1 I2 I3 ...
    for (size_t index = dfa.get_work_index();
         !dfa.no_status_left(); index = dfa.move_next()) {
        // status to be deal
        auto status = dfa.get_status(index);
        // iterms in status
        auto items = status.get_content();
        // relation from status_index to other
        auto relation = dfa.get_relation(index);
#ifdef DEBUG_PARSING_TABLE
        std::cout << "\nDEBUG relation: " << index << "- > " << std::endl;
        for (auto m : relation) {
            std::cout << m.first << " -> " << m.second << std::endl;
        }
#endif
        // goto toble
        for (auto m : relation) {
            if (dfa.get_token(m.first).is_state_token()) {
                parsing_table.add_into_goto(index, dfa.get_token(m.first), m.second);
            }
        }
        // action table
        for (auto item : items) {
            // for action table
            if (item.is_end()) {
                // is special production
                if (item.get_which() == grammar.get_start_state()
                    && item.get_index() == grammar.get_start_index()) {
                    // accept
                    parsing_table.add_into_action(index, END_STATE, ACCEPT);
                } else if (item.get_which() != grammar.get_start_state()) {
                    // 规约
                    parsing_table.add_into_action(index, item.get_end_symbol(),
                        std::string(REDUCTION) + " "
                            + item.get_which() + "  "
                            + std::to_string(item.get_index()));
                }
                continue;
            }
            // [A->?.a?,b] && go(status, a) = status2 ->
            // action[status_now_id, status2_id] = move in (status_2)
            Token next_token = item.after_decimal(grammar);
#ifdef DEBUG_PARSING_TABLE_GOTO
            std::cout << "DEBUG FOR ACTION TABLE " << std::endl;
            std::cout << "next token is: " << std::endl;
            std::cout << "is null state: " << next_token.is_null_token()
                      << std::endl;
            std::cout << "is state token: " << next_token.is_state_token()
                      << " " << next_token.get_state() << std::endl;
            std::cout << "is id: " << next_token.is_id() << " "
                      << next_token.get_token() << std::endl;
            std::cout << "is symbol ? : " << next_token.get_token()
                      << next_token.get_attr() << std::endl;
            std::cout << std::endl;
            std::cout << (relation.find(next_token.get_token()) != relation.end())
                      << std::endl;
            std::cout << std::endl;
#endif
            if (!next_token.is_state_token() // && !next_token.is_null_token()
                && relation.find(dfa.get_token_id(next_token)) != relation.end()) {
                // 移入 并进入状态 next
                parsing_table.add_into_action(index, next_token.get_token(),
                    std::string(MOVE_IN) + " "
                        + std::to_string(relation.at(dfa.get_token_id(next_token))));
            } else if (next_token.is_null_token()) {
                std::cout << "null state need to be dealed in grammar_tool.cpp at 185"
                          << std::endl;
            }
        }
    }
}

std::unordered_set<int> GrammarDealer::first(const std::vector<Token>& left)
{
    times = 0;
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
    ++times;
    if (times > 100)
        return std::unordered_set<int>();
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
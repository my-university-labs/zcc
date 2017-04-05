/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 11:52:25 PM CST */

#include "dfa.h"
#include <iostream>

DFA::DFA(Status& status)
{
    dstatus.clear();
    dstatus.push_back(status);
    start_status = 0;
}

size_t DFA::add_status(const Status& status1, const Token& token, const Status& status2)
{
#ifdef DEBUG_DFA
    std::cout << get_status_id(status1) << " -> " << token.get_attr() << " | "
              << token.get_token() << " " << get_status_id(status2) << std::endl;
    std::cout << "status1 size -> " << status1.size() << " status2 size -> "
              << status2.size() << std::endl;
    std::cout << std::endl;
#endif
    size_t start = 0, end = 0, tloc = 0;
    bool find_s = false, find_e = false, find_t = false;
    for (size_t i = 0; i < dstatus.size(); ++i) {
        if (dstatus[i] == status1) {
            find_s = true;
            start = i;
        }
        if (dstatus[i] == status2) {
            find_e = true;
            end = i;
        }
    }
    if (!find_s) {
        // deal error
        std::cout << dstatus.size() << std::endl;
        exit(0);
    }
    for (size_t i = 0; i < dtokens.size(); ++i) {
        if (dtokens[i] == token) {
            find_t = true;
            tloc = i;
            break;
        }
    }
    if (!find_t) {
        dtokens.push_back(token);
        tloc = dtokens.size() - 1;
    }
    if (!find_e) {
        dstatus.push_back(status2);
        end = dstatus.size() - 1;
    }
    // deal relation
    // 没有I0
    if (relation.find(start) == relation.end()) {
        std::map<size_t, size_t> tmp{
            { tloc, end },
        };
        relation[start] = tmp;
        return end;
    } else if (relation[start].find(tloc) == relation[start].end()) {
        // 有I0 没有 转移字符
        relation[start][tloc] = end;
        return end;
    } else {
        // 两者都有
        dstatus[relation[start][tloc]] += status2;
        return relation[start][tloc];
    }
}

size_t DFA::add_status(const size_t status1, const Token& token, const Status& status2)
{
    if (status1 < dstatus.size())
        return add_status(dstatus[status1], token, status2);
    else {
        // deal error
        return ERROR;
    }
}

size_t DFA::add_start_status(const Status& status)
{
    clear();
    dstatus.push_back(status);
    start_status = 0;
    return start_status;
}
Status DFA::get_status(size_t id) const
{
    if (id < dstatus.size())
        return dstatus[id];
    else {
        // deal error
        Status tmp;
        return tmp;
    }
}

template <typename T>
size_t DFA::go(const size_t id, const T& t) const
{
    size_t tloc;
    bool find_t = false;
    for (size_t i = 0; i < dtokens.size(); ++i) {
        if (dtokens[i] == t) {
            find_t = true;
            tloc = i;
            break;
        }
    }
    if (relation.find(id) != relation.end() && relation.at(id).find(tloc) != relation.at(id).end()) {
        return relation.at(id).at(tloc);
    } else {
        // deal error
        return ERROR;
    }
}

void DFA::check(Grammar& grammar)
{
    std::cout << "# Check Dfa #" << std::endl;
    std::cout << "Stauts size: " << dstatus.size() << std::endl;
    std::cout << "Token size: " << dtokens.size() << std::endl;
    std::cout << "# Show all Status ------------> " << std::endl;

    for (size_t i = 0; i < dstatus.size(); ++i) {
        std::cout << "Status " << i << std::endl;
        for (auto it : dstatus[i].get_content()) {
            std::cout << it.get_which() << " -> "; //<< it.get_index() << " " << it.get_decimal() << " " << it.get_production_size() << std::endl;
            auto p = grammar.get_production(it.get_which(), it.get_index());
            for (auto t : p) {
                if (t.is_state_token()) {
                    std::cout << " " << t.get_state();
                } else if (t.is_null_token()) {
                    std::cout << " "
                              << "null[" << t.get_attr() << "]";
                } else {
                    if (t.get_token() == ID)
                        std::cout << " id ";
                    else
                        std::cout << " " << get_token_info(t.get_token());
                }
            }
            std::cout << "     |     " << it.get_decimal() << " ";
            if (it.get_end_symbol() == END_STATE)
                std::cout << "#";
            else
                std::cout << get_token_info(it.get_end_symbol());
            std::cout << std::endl;
        }
    }
    std::cout << "# Show all token --------------> " << std::endl;
    for (size_t i = 0; i < dtokens.size(); ++i) {
        std::cout << "Token " << i << std::endl;
        std::cout << dtokens[i].get_token() << " -> " << dtokens[i].get_attr();
        if (!dtokens[i].is_null_token() && !dtokens[i].is_state_token()) {
            std::cout << " -> " << get_token_info(dtokens[i].get_token());
        }
        std::cout << std::endl;
    }

    std::cout << "# Show Relation ---------------> " << std::endl;

    for (auto& m : relation) {
        std::cout << "new relation: " << m.first << std::endl;
        for (auto& i : m.second) {
            std::cout << i.first << " -> " << i.second << std::endl;
        }
    }
}

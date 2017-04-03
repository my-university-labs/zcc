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

size_t DFA::add_status(Status& status1, Token& token, Status& status2)
{
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
        ;
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
    if (relation.find(start) == relation.end()) {
        std::map<size_t, size_t> tmp{
            { tloc, end },
        };
        relation[start] = tmp;
        return end;
    } else if (relation[start].find(tloc) != relation[start].end()) {
        relation[start][tloc] = end;
        return end;
    } else {
        dstatus[relation[start][tloc]] += status2;
        return relation[start][tloc];
    }
}

size_t DFA::add_status(size_t status1, Token& token, Status& status2)
{
    if (status1 < dstatus.size())
        return add_status(dstatus[status1], token, status2);
    else {
        // deal error
        return ERROR;
    }
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

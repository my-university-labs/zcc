/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 11:51:07 PM CST */
#ifndef TOOLS_GRAMMAR_DFA_H
#define TOOLS_GRAMMAR_DFA_H

#include "item.h"
#include "status.h"
#include "token.h"
#include "unstd.h"
#include <map>
#include <vector>

class DFA {
public:
    DFA() {}
    DFA(Status& status);

    // status1 -token-> status2
    size_t add_status(Status& status1, Token& token, Status& status2);

    size_t add_status(size_t status1, Token& token, Status& status2);

    size_t add_start_status(const Status& status);

    Status get_status(size_t id) const;

    void clear()
    {
        dstatus.clear();
        dtokens.clear();
        relation.clear();
        start_status = 0;
    }

    template <typename T>

    size_t go(const size_t id, const T& t) const;

    inline size_t get_work_index() const
    {
        return work_index;
    }

    inline size_t move_next()
    {
        ++work_index;
        return work_index;
    }
    inline size_t get_status_times() const
    {
        return dstatus.size();
    }
    inline bool no_status_left() const
    {
        return (work_index >= dstatus.size() ? true : false);
    }

private:
    size_t work_index = 0;

    size_t start_status;
    // save every status of dfa
    std::vector<Status> dstatus;
    // save every transfer token
    std::vector<Token> dtokens;
    // the relation between status and token
    // : map<status_id1, map< token_id, status_id2>>
    // : status1 -token-> status2
    std::map<size_t, std::map<size_t, size_t> > relation;
};
#endif

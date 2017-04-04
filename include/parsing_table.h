/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 12:05:50 AM CST */

#ifndef SRC_PARSER_PARSINGTABLE_H
#define SRC_PARSER_PARSINGTABLE_H

#include "status.h"
#include "token.h"
#include <map>
#include <string>

class ParsingTable {
public:
    typedef std::map<size_t, std::map<size_t, std::string> > action_type;
    typedef std::map<size_t, std::map<Token, size_t> > goto_type;
    ParsingTable()
    {
        action_table.clear();
        goto_table.clear();
    }
    // have a table file then load it
    ParsingTable(std::string tablef);

private:
    // action table;
    // [status id, terminal symbol] -> action
    action_type action_table;
    // goto table
    // [status id, terminal symbol] -> new status
    goto_type goto_table;
};
#endif

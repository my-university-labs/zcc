/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 12:05:50 AM CST */

#ifndef SRC_PARSER_PARSINGTABLE_H
#define SRC_PARSER_PARSINGTABLE_H

#include "status.h"
#include "token.h"
#include <fstream>
#include <map>
#include <set>
#include <string>

class ParsingTable {
public:
    typedef std::map<size_t, std::map<int, std::string> > action_table_type;
    typedef std::map<size_t, std::map<Token, size_t> > goto_table_type;
    typedef struct {
        // move in or reduction
        std::string action;
        // if action is move in then jump to this status
        size_t next_status;
        // if action is reduction then use this production to reduct
        std::string which;
        size_t index;
        // is error
        bool error;
        std::map<int, std::string> next_token_should_be;
    } action_type;

    typedef struct {
        // goto next status
        size_t next_status;
        bool error;
    } goto_type;

    ParsingTable()
    {
        action_table.clear();
        goto_table.clear();
    }
    // have a table file then load it
    ParsingTable(std::string tablef);

    void add_into_action(const size_t status, const int terminal_symbol, const std::string& action);

    void add_into_goto(const size_t status, const Token& token, const size_t new_status);

    void save_table_to_file();

    action_type query_action(size_t start_status, int terminal_symbol) const;

    goto_type query_goto(size_t status, const Token& token) const;

    void output_action_table();

    void output_goto_table();

    size_t get_default_start_state() const { return default_start_state; }

private:
    const std::string action_flag = "$ACTION_TABLE";
    const std::string goto_flag = "$GOTO_TABLE";
    const std::string new_flag = "$NEW";
    const size_t default_start_state = 0;
    // action table;
    // [status id, terminal symbol] -> action
    action_table_type action_table;
    // goto table
    // [status id, terminal symbol] -> new status
    goto_table_type goto_table;
};
#endif

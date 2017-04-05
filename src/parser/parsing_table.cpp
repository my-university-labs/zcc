/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 12:05:18 AM CST */

#include "parsing_table.h"

#include <algorithm>
#include <iostream>

ParsingTable::ParsingTable(std::string tablef)
{
}

void ParsingTable::add_into_action(const size_t status, const int terminal_symbol, const std::string& action)
{
    if (action_table.find(status) != action_table.end()) {
        if ((action_table[status]).find(terminal_symbol) != (action_table[status]).end()) {
            std::cerr << "Error At parsing_table.cpp 14: grammar error" << std::endl;
            //exit(2);
        } else {
            action_table[status][terminal_symbol] = action;
        }
    } else {
        std::map<int, std::string> tmp;
        tmp[terminal_symbol] = action;
        action_table[status] = tmp;
    }
}

void ParsingTable::add_into_goto(const size_t status, const Token& token, const size_t new_status)
{
    if (goto_table.find(status) != goto_table.end()) {
        if (goto_table[status].find(token) != goto_table[status].end()) {
            std::cerr << "Error At parsing_table.cpp 29: grammar error" << std::endl;
            //exit(2);
        } else {
            goto_table[status][token] = new_status;
        }
    } else {
        std::map<Token, size_t> tmp;
        tmp[token] = new_status;
        goto_table[status] = tmp;
    }
}

void ParsingTable::output_action_table()
{
    for (auto& m : action_table) {
        std::cout << m.first << std::endl;
        for (auto p : m.second) {
            std::cout << p.first << " -> " << p.second << std::endl;
        }
        std::cout << " ------------------- " << std::endl;
    }
}

void ParsingTable::output_goto_table()
{
    for (auto& m : goto_table) {
        std::cout << m.first << std::endl;
        for (auto p : m.second) {
            std::cout << p.first.get_state() << " -> " << p.second << std::endl;
        }
        std::cout << " ------------------------ " << std::endl;
    }
}
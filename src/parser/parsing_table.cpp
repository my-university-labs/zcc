/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 12:05:18 AM CST */

#include "parsing_table.h"

#include <algorithm>
#include <iostream>
#include <sstream>

ParsingTable::ParsingTable(std::string tablef)
{
    std::cout << "load parsing table info" << std::endl;
    std::ifstream in(tablef);
    if (in) {
        std::string line;
        bool read_action = false;
        bool read_goto = false;
        int Y;
        size_t X, svalue;
        std::string action, state;
        while (std::getline(in, line)) {
            if (line == action_flag) {
                read_action = true;
                read_goto = false;
            } else if (line == goto_flag) {
                read_action = false;
                read_goto = true;
            } else if (line == new_flag) {
                std::getline(in, line);
                std::istringstream is1(line);
                is1 >> X;
            } else {
                if (read_action) {
                    std::istringstream is2(line);
                    is2 >> Y;
                    std::getline(in, action);
                    add_into_action(X, Y, action);
                } else if (read_goto) {
                    Token token(line);
                    std::getline(in, line);
                    std::istringstream is3(line);
                    is3 >> svalue;
                    add_into_goto(X, token, svalue);
                }
            }
        }
        in.close();
    } else {
        // deal error
        std::cerr << "no parsing table info input" << std::endl;
        exit(1);
    }
}

void ParsingTable::add_into_action(const size_t status, const int terminal_symbol, const std::string& action)
{
#ifdef DEBUG_PARSING_TABLE
    std::cout << "DEBUG_ACTION" << status << " - " << terminal_symbol << " -> " << action << std::endl;
#endif
    if (action_table.find(status) != action_table.end()) {
        if ((action_table[status]).find(terminal_symbol) == (action_table[status]).end()) {
            action_table[status][terminal_symbol] = action;
        } else if ((action_table[status]).find(terminal_symbol) != (action_table[status]).end()
            && action_table[status][terminal_symbol] != action) {
            std::cerr << "Error At parsing_table.cpp add_into_action: grammar error" << std::endl;
            std::cerr << "More Info: " << std::endl
                      << "from: " << status << std::endl
                      << "meet: " << terminal_symbol << std::endl
                      << "action table had: " << action_table[status][terminal_symbol] << std::endl
                      << "want insert: " << action << std::endl;
            exit(2);
        } else {
            // do nothing
            ;
        }
    } else {
        std::map<int, std::string> tmp;
        tmp[terminal_symbol] = action;
        action_table[status] = tmp;
    }
}

void ParsingTable::add_into_goto(const size_t status, const Token& token, const size_t new_status)
{
#ifdef DEBUG_PARSING_TABLE
    std::cout << "DEBUG_GOTO" << status << " - " << token.get_token() << " " << token.get_attr() << " -> " << new_status << std::endl;
#endif

    if (goto_table.find(status) != goto_table.end()) {
        if (goto_table[status].find(token) == goto_table[status].end()) {
            goto_table[status][token] = new_status;
        } else if (goto_table[status].find(token) != goto_table[status].end()
            && goto_table[status][token] != new_status) {
            std::cerr << "Error At parsing_table.cpp 29: grammar error" << std::endl;
            std::cerr << "More Info: " << status
                      << " " << token.get_token()
                      << " " << goto_table[status][token]
                      << " " << new_status << std::endl;
            exit(2);
        } else {
            ; // do nothing
        }
    } else {
        std::map<Token, size_t> tmp;
        tmp[token] = new_status;
        goto_table[status] = tmp;
    }
}
// save action table and goto table into file
// default file name is PARSING_TABLE_FILE_NAME defined in unstd.h
// the rule how to save table infomation is:
// when meet std::string action_flag, start to write action info into next line
// 0. when meet std::string new_flag, start to write X status ([X, terminal_symbol] = action)
// 1. then write terminal_symbol next line
// 2. then write action next line
// repeat 1 2
// when meet new_flag start from 0 again
// goto table as same as action
void ParsingTable::save_table_to_file()
{
    std::ofstream out(PARSING_TABLE_FILE_NAME);
    if (out) {
        out << action_flag << std::endl;
        for (auto& m : action_table) {
            out << new_flag << std::endl;
            out << m.first << std::endl;
            for (auto values : m.second) {
                out << values.first << std::endl
                    << values.second << std::endl;
            }
        }
        out << goto_flag << std::endl;
        for (auto& m : goto_table) {
            out << new_flag << std::endl;
            out << m.first << std::endl;
            for (auto values : m.second) {
                out << values.first.get_state() << std::endl
                    << values.second << std::endl;
            }
        }
        out.close();
    } else {
        // deal error
        std::cerr << "can not open file " << PARSING_TABLE_FILE_NAME
                  << " to save parsing table infomation" << std::endl;
        exit(0);
    }
}

ParsingTable::action_type ParsingTable::query_action(size_t start_status, int terminal_symbol) const
{
    action_type result;
    if (action_table.find(start_status) != action_table.cend()
        && action_table.at(start_status).find(terminal_symbol)
            != action_table.at(start_status).cend()) {
        result.error = false;
        std::istringstream is(action_table.at(start_status).at(terminal_symbol));
        is >> result.action;
        if (result.action == MOVE_IN) {
            is >> result.next_status;
        } else if (result.action == REDUCTION) {
            is >> result.which >> result.index;
        } else if (result.action == ACCEPT) {
            ; // accept
        } else {
            // deal error
            std::cerr << "Error at query_action" << std::endl;
        }

    } else {
        result.error = true;
    }
    return result;
}
ParsingTable::goto_type ParsingTable::query_goto(size_t status, const Token& token) const
{
    goto_type result;
    if (goto_table.find(status) != goto_table.cend()
        && goto_table.at(status).find(token) != goto_table.at(status).cend()) {
        result.next_status = goto_table.at(status).at(token);
        result.error = false;
        result.next_status = goto_table.at(status).at(token);
    } else {
        result.error = true;
    }
    return result;
}

void ParsingTable::output_action_table()
{
    for (auto& m : action_table) {
        std::cout << "from status : " << m.first << std::endl;
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
/* author: dongchangzhang */
/* time: Thu 09 Mar 2017 01:59:17 PM CST */

#ifndef SRC_PLUGIN_SYMBOLTABLEMANAGER_H
#define SRC_PLUGIN_SYMBOLTABLEMANAGER_H

#include "symboltable.h"
#include <string>
#include <unordered_map>

#define START_INDEX 0

class SymbolTableManager {
public:
    SymbolTableManager() = default;
    SymbolTable::addr_type install_id(const std::string& id);
    SymbolTable::addr_type install_value(int val);
    SymbolTable::addr_type install_value(char val);
    void insert();

private:
    SymbolTable s;
    size_t main_table;
    size_t cursor;
    std::unordered_map<size_t, size_t> relation;
    std::unordered_map<size_t, SymbolTable> symbol_tables;

    size_t timer = 0;
    inline size_t do_timer_increase() { return ++timer; }
    inline size_t do_create_new_table(size_t parent);
    inline void do_destroy_table(size_t which);
    inline void do_leave_table(size_t from_which);
    inline void do_goto_table(size_t goto_which);
};

inline size_t SymbolTableManager::do_create_new_table(size_t parent)
{
    size_t new_table_index = do_timer_increase();
    relation[new_table_index] = parent;
    symbol_tables[new_table_index] = SymbolTable();
    return new_table_index;
}

#endif

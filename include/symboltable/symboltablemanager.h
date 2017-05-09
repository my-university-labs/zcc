/* author: dongchangzhang */
/* time: Thu 09 Mar 2017 01:59:17 PM CST */

#ifndef SRC_PLUGIN_SYMBOLTABLEMANAGER_H
#define SRC_PLUGIN_SYMBOLTABLEMANAGER_H

#include "symboltable.h"
#include <string>
#include <unordered_map>
#include <vector>

#define START_INDEX 0

class SymbolTableManager {
public:
    SymbolTableManager();
    addr_type install_id(const std::string& id);
    addr_type install_value(int val);
    addr_type install_value(char val);
    void show_addr(addr_type& addr);
    void show_addr_content(addr_type& addr);
    void declare_define_variable(int type, addr_type& addr_id);
    void declare_define_variable(int type, addr_type& addr_id, addr_type& addr_value);
    void variable_assignment(addr_type& id, addr_type& value);
    void array_assignment(addr_type& id, addr_type& value);
    void value_assignment(addr_type& addr, int value);

    addr_type conver_to_bool(addr_type& addr);

    void declare_array(int type, addr_type& addr_id, std::vector<int>& array_times);
    addr_type get_array_element_addr(addr_type& addr_id, std::vector<int>& array_times);

    int get_int(addr_type& addr);
    char get_char(addr_type& addr);

private:
    // main symboltable
    size_t main_table;
    // which symboltable is used now
    size_t cursor;
    // symboltable -> symboltable's parent
    std::unordered_map<size_t, size_t> relation;
    // index -> symboltable
    std::unordered_map<size_t, SymbolTable> symbol_tables;

    // when create a new symboltable, use this index it
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

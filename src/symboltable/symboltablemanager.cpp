/* author: dongchangzhang */
/* time: Thu Apr 20 14:48:28 2017 */

#include "symboltablemanager.h"
#include <iostream>

SymbolTableManager::SymbolTableManager()
{
    main_table = do_create_new_table(START_INDEX);
    cursor = main_table;
}
addr_type SymbolTableManager::install_id(const std::string& id)
{
    return symbol_tables[cursor].install_id(id);
}
addr_type SymbolTableManager::install_value(int val)
{
    return symbol_tables[cursor].install_value(val);
}
addr_type SymbolTableManager::install_value(char val)
{
    return symbol_tables[cursor].install_value(val);
}
void SymbolTableManager::show_addr(addr_type& addr)
{
    symbol_tables[cursor].show_addr(addr);
}
void SymbolTableManager::show_addr_content(addr_type& addr)
{
    symbol_tables[cursor].show_addr_content(addr);
}

int SymbolTableManager::get_int(addr_type& addr)
{
    return symbol_tables[cursor].get_int(addr);
}
char SymbolTableManager::get_char(addr_type& addr)
{
    return symbol_tables[cursor].get_char(addr);
}
void SymbolTableManager::declare_define_variable(int type, addr_type& addr_id)
{
    addr_type addr;
    symbol_tables[cursor].declare_define_variable(type, addr_id, addr);
}
void SymbolTableManager::declare_define_variable(int type, addr_type& addr_id, addr_type& addr_value)
{
    symbol_tables[cursor].declare_define_variable(type, addr_id, addr_value);
}
void SymbolTableManager::declare_array(int type, addr_type& addr_id, std::vector<int>& array_times)
{
    symbol_tables[cursor].declare_array(type, addr_id, array_times);
}
addr_type SymbolTableManager::get_array_element_addr(addr_type& addr_id, std::vector<int>& array_times)
{
    return symbol_tables[cursor].get_array_element_addr(addr_id, array_times);
}
void SymbolTableManager::variable_assignment(addr_type& id, addr_type& value)
{
    symbol_tables[cursor].variable_assignment(id, value);
}
void SymbolTableManager::array_assignment(addr_type& id, addr_type& value)
{
    symbol_tables[cursor].array_assignment(id, value);
}
void SymbolTableManager::value_assignment(addr_type& addr, int value)
{
    symbol_tables[cursor].value_assignment(addr, value);
}

addr_type SymbolTableManager::conver_to_bool(addr_type& addr)
{
    return symbol_tables[cursor].conver_to_bool(addr);
}

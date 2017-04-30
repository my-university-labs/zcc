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
void SymbolTableManager::print_addr(addr_type& addr)
{
    symbol_tables[cursor].print_addr(addr);
}
void SymbolTableManager::print_addr_info(addr_type& addr)
{
    symbol_tables[cursor].print_addr_info(addr);
}

int SymbolTableManager::get_int(addr_type& addr)
{
    return symbol_tables[cursor].get_int(addr);
}
char SymbolTableManager::get_char(addr_type& addr)
{
    return symbol_tables[cursor].get_char(addr);
}
void SymbolTableManager::id_assagin(int type, addr_type& addr_id)
{
    addr_type addr;
    symbol_tables[cursor].id_assagin(type, addr_id, addr);
}
void SymbolTableManager::id_assagin(int type, addr_type& addr_id, addr_type& addr_value)
{
    symbol_tables[cursor].id_assagin(type, addr_id, addr_value);
}
void SymbolTableManager::array_assagin(int type, addr_type& addr_id, std::vector<size_t>& array_times)
{
    symbol_tables[cursor].array_assagin(type, addr_id, array_times);
}
void SymbolTableManager::assign(addr_type& id, addr_type& value)
{
    symbol_tables[cursor].assign(id, value);
}
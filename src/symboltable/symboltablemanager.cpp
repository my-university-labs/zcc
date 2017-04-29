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
    std::cout << "--- symbol table insert id ---" << id << std::endl;
    return symbol_tables[cursor].install_id(id);
}
addr_type SymbolTableManager::install_value(int val)
{
    std::cout << "--- symbol table insert value ---" << val << std::endl;
    return symbol_tables[cursor].install_value(val);
}
addr_type SymbolTableManager::install_value(char val)
{
    std::cout << "--- symbol table insert value ---" << val << std::endl;
    return symbol_tables[cursor].install_value(val);
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
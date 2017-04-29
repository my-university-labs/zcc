/* author: dongchangzhang */
/* time: Thu 09 Mar 2017 02:01:19 PM CST */

#include "symboltable.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static void print_addr(addr_type& addr)
{
    std::cout << "Addr -> " << addr.index << " " << addr.type << " " << addr.location << std::endl;
}

addr_type SymbolTable::install_id(const std::string& id)
{
    if (find(symbols.cbegin(), symbols.cend(), id) == symbols.cend()) {
        addr_type addr;
        addr.index = symbols.size();
        addr.type = ST_ID;
        symbols.push_back(id);
        // print_addr(addr);
        return addr;
    } else {
        // error
        std::cerr << "redefine symbol -> " << id << std::endl;
        std::cerr << "terminate" << std::endl;
        exit(1);
    }
}
addr_type SymbolTable::install_value(int val)
{
    value_info_type vit;
    addr_type addr;
    vit.type = ST_INT;
    vit.value.ivalue = val;
    addr.type = ST_INT;
    addr.location = value_informations.size();
    value_informations.push_back(vit);
    // print_addr(addr);

    return addr;
}
addr_type SymbolTable::install_value(char val)
{
    value_info_type vit;
    addr_type addr;
    vit.type = ST_CHAR;
    vit.value.ivalue = val;
    addr.type = ST_CHAR;
    addr.location = value_informations.size();
    value_informations.push_back(vit);
    // print_addr(addr);

    return addr;
}

void SymbolTable::print_addr_info(addr_type& addr)
{
    if (addr.type == ST_ID)
        std::cout << symbols[addr.index];
    else if (addr.type == ST_INT)
        std::cout << value_informations[addr.location].value.ivalue;
    else if (addr.type == ST_CHAR)
        std::cout << value_informations[addr.location].value.cvalue;
    else
        std::cout << "NONE";
}

int SymbolTable::get_int(addr_type& addr)
{
    if (addr.type == ST_INT) {
        if (addr.location < value_informations.size())
            return value_informations[addr.location].value.ivalue;
    }
    std::cerr << "error at symbol int" << std::endl;
    exit(1);
}
char SymbolTable::get_char(addr_type& addr)
{
    if (addr.type == ST_CHAR) {
        if (addr.location < value_informations.size())
            return value_informations[addr.location].value.cvalue;
    }
    std::cerr << "error at symbol char" << std::endl;
    exit(1);
}
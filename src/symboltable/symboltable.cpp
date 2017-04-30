/* author: dongchangzhang */
/* time: Thu 09 Mar 2017 02:01:19 PM CST */
#include "symboltable.h"
#include "token.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void SymbolTable::print_addr(addr_type& addr)
{
    std::cout << "$" << addr.index << addr.type << addr.location;
}

addr_type SymbolTable::install_id(const std::string& id)
{
    addr_type addr;
    auto ret = find(symbols.begin(), symbols.end(), id);
    if (ret != symbols.cend()) {
        size_t index = ret - symbols.begin();
        // std::cout << index << " " << symbols_relation.size() << std::endl;
        if (symbols_relation.find(index) != symbols_relation.end()) {
            return symbols_relation[index];
        }
        addr.index = index;
    } else {
        addr.index = symbols.size();
        symbols.push_back(id);
    }
    addr.type = ST_ID;
    return addr;
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
// declare
void SymbolTable::id_assagin(int type, addr_type& addr_id, addr_type& addr_value)
{
    if (symbols_relation.find(addr_id.index) != symbols_relation.end()) {
        std::cerr << "redefine error" << std::endl;
        exit(0);
    }
    if (type == INT) {
        addr_id.type = ST_INT;
        addr_id.location = addr_value.location;
        if (addr_id.location > value_informations.size()) {

            addr_id.location = 0;
        }
        symbols_relation[addr_id.index] = addr_id;
    }
}
// declare
void SymbolTable::array_assagin(int type, addr_type& addr_id, std::vector<size_t>& array_times)
{
    if (symbols_relation.find(addr_id.index) != symbols_relation.end()) {
        std::cerr << "redefine error" << std::endl;
        exit(0);
    }
}

void SymbolTable::assign(addr_type& id, addr_type& value)
{
    value.index = id.index;
    symbols_relation[id.index] = value;
}
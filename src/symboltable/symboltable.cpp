/* author: dongchangzhang */
/* time: Thu 09 Mar 2017 02:01:19 PM CST */
#include "symboltable.h"
#include "token.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

addr_type SymbolTable::install_id(const std::string& id)
{
    addr_type addr;
    auto ret = find(symbols.begin(), symbols.end(), id);
    if (ret != symbols.cend()) {
        // have install it, return it
        size_t index = ret - symbols.begin();
        if (symbols_relation.find(index) != symbols_relation.end()) {
            return symbols_relation[index];
        }
        addr.index = index;
    } else {
        // not find, install a new one
        addr.index = symbols.size();
        symbols.push_back(id);
    }
    addr.type = ADDR_IS_ID;
    addr.addition_info = VALUE_TYPE_IS_NONE;
    return addr;
}
addr_type SymbolTable::install_value(int val)
{
    value_info_type vit;
    addr_type addr;
    vit.type = VALUE_TYPE_IS_INT;
    vit.value.ivalue = val;
    addr.type = ADDR_IS_VALUE;
    addr.addition_info = VALUE_TYPE_IS_INT;
    addr.location = value_informations.size();
    value_informations.push_back(vit);
    return addr;
}
addr_type SymbolTable::install_value(char val)
{
    value_info_type vit;
    addr_type addr;
    vit.type = VALUE_TYPE_IS_CHAR;
    vit.value.ivalue = val;
    addr.type = ADDR_IS_VALUE;
    addr.addition_info = VALUE_TYPE_IS_CHAR;
    addr.location = value_informations.size();
    value_informations.push_back(vit);
    return addr;
}

void SymbolTable::show_addr_content(addr_type& addr)
{
    if (addr.type == ADDR_IS_ID)
        std::cout << symbols[addr.index];
    else if (addr.type == ADDR_IS_ARRAY) {
        std::cout << symbols[addr.index];
        for (auto t : addr.array_info)
            std::cout << "[" << t << "]";
    } else if (addr.type == ADDR_IS_VALUE) {
        if (addr.tmp)
            show_addr(addr);
        else if (addr.addition_info == VALUE_TYPE_IS_INT)
            std::cout << value_informations[addr.location].value.ivalue;
        else if (addr.type == VALUE_TYPE_IS_CHAR)
            std::cout << value_informations[addr.location].value.cvalue;
        else
            std::cout << "NONE";
    }
}

// declare
void SymbolTable::declare_define_variable(int type, addr_type& addr_id, addr_type& addr_value)
{
    if (symbols_relation.find(addr_id.index) != symbols_relation.end()) {
        std::cerr << "redefine error" << std::endl;
        exit(0);
    }
    if (type == INT) {
        addr_id.addition_info = VALUE_TYPE_IS_INT;
        addr_id.location = addr_value.location;
        symbols_relation[addr_id.index] = addr_id;
    }
}
// declare
void SymbolTable::declare_array(int type, addr_type& addr_id, std::vector<int>& array_times)
{
    if (symbols_relation.find(addr_id.index) != symbols_relation.end()) {
        std::cerr << "redefine error" << std::endl;
        exit(0);
    }
    if (type == INT) {
        addr_id.type = ADDR_IS_ARRAY;
        addr_id.addition_info = VALUE_TYPE_IS_INT;
        addr_id.location = array_informations.size();
        symbols_relation[addr_id.index] = addr_id;
        array_info_type new_array;
        new_array.type = VALUE_TYPE_IS_INT;
        new_array.array_times = array_times.size();
        new_array.times_info = array_times;
        new_array.malloc_place();
        array_informations.push_back(new_array);
    }
}

addr_type SymbolTable::get_array_element_addr(addr_type& addr_id, std::vector<int>& array_times)
{
    addr_type addr = symbols_relation[addr_id.index];
    addr.array_info = array_times;
    return addr;
}
void SymbolTable::variable_assignment(addr_type& id, addr_type& value)
{
    addr_type new_value = value;
    new_value.type = id.type;
    new_value.index = id.index;
    symbols_relation[id.index] = new_value;
}
void SymbolTable::value_assignment(addr_type& addr, int value)
{
    if (addr.type == ADDR_IS_VALUE && addr.addition_info == VALUE_TYPE_IS_INT)
        value_informations[addr.location].value.ivalue = value;
    else
        std::cerr << "value assign false" << std::endl;
}
void SymbolTable::array_assignment(addr_type& array_element, addr_type& value)
{
    size_t index = get_array_index(array_element);
    array_informations[array_element.location].array_values[index].value.ivalue = value_informations[value.location].value.ivalue;
}
size_t SymbolTable::get_array_index(addr_type& array_element)
{
    auto times = array_informations[array_element.location].times_info;
    auto target = array_element.array_info;
    if (times.size() != target.size()) {
        std::cerr << "array error1 " << times.size() << " " << target.size() << std::endl;
        return 0;
    }
    size_t index = 0;
    for (size_t i = 0; i < times.size() - 1; ++i) {
        if (target[i] < times[i]) {
            index += target[i] * times[i];
        } else {
            std::cerr << "array error2" << std::endl;
            return 0;
        }
    }
    if (target[times.size() - 1] < times[times.size() - 1]) {
        index += target[times.size() - 1];
    } else {
        std::cerr << "array error3" << std::endl;
        return 0;
    }
    return index;
}
void SymbolTable::show_addr(addr_type& addr)
{
    std::cout << "$" << addr.type << addr.addition_info << addr.index << addr.location;
    for (auto c : addr.array_info)
        std::cout << c;
}
int SymbolTable::get_int(addr_type& addr)
{
    if (addr.type == ADDR_IS_ARRAY && addr.addition_info == VALUE_TYPE_IS_INT) {
        size_t index = get_array_index(addr);
        return array_informations[addr.location].array_values[index].value.ivalue;

    } else if (addr.addition_info == VALUE_TYPE_IS_INT) {
        if (addr.location < value_informations.size()) {
            return value_informations[addr.location].value.ivalue;
        }
    }
    std::cerr << "error at symbol int" << std::endl;
    exit(1);
}
char SymbolTable::get_char(addr_type& addr)
{
    if (addr.type == VALUE_TYPE_IS_CHAR) {
        if (addr.location < value_informations.size())
            return value_informations[addr.location].value.cvalue;
    }
    std::cerr << "error at symbol char" << std::endl;
    exit(1);
}
addr_type SymbolTable::conver_to_bool(addr_type& addr)
{
    addr_type new_addr;
    new_addr.type = ADDR_IS_BOOL;
    if (addr.type == ADDR_IS_BOOL)
        new_addr.addition_info = addr.addition_info;
    else if (addr.addition_info == VALUE_TYPE_IS_INT) {
        new_addr.addition_info = get_int(addr) != 0 ? 1 : 0;
    } else {
        show_addr(addr);
        new_addr.addition_info = 0;
    }
    return addr;
}
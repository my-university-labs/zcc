/* author: dongchangzhang */
/* time: Thu 09 Mar 2017 01:59:17 PM CST */

#ifndef SRC_PLUGIN_SYMBOLTABLE_H
#define SRC_PLUGIN_SYMBOLTABLE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#define ADDR_IS_ID 101
#define ADDR_IS_VALUE 102
#define ADDR_IS_FUNCTION 103
#define ADDR_IS_NONE 109

#define VALUE_TYPE_IS_INT 201
#define VALUE_TYPE_IS_CHAR 202
#define VALUE_TYPE_IS_FLOAT 203
#define VALUE_TYPE_IS_DOUBLE 204
#define VALUE_TYPE_IS_VOID 205
#define VALUE_TYPE_IS_NONE 209

// information for value and value definenation
struct value_info_type {
    int type;
    union {
        int ivalue;
        float fvalue;
        char cvalue;
    } value;
};
// array
struct array_info_type {
    size_t array_times;
    int type;
    std::vector<size_t> times_info;
};
// function
struct func_info_type {
    int return_type;
    size_t arg_times;
};
// addr -> how to locate info about id
struct addr_type {
    addr_type() = default;
    int type;
    int addition_info;
    size_t index = 0;
    size_t location = 0;
    addr_type(const addr_type& addr)
    {
        type = addr.type;
        addition_info = addr.addition_info;
        index = addr.index;
        location = addr.location;
    }
    addr_type& operator=(const addr_type& addr)
    {
        type = addr.type;
        addition_info = addr.addition_info;
        index = addr.index;
        location = addr.location;
        return *this;
    }
    bool operator==(const addr_type& addr) const
    {
        return addr.type == type
            && addr.addition_info == addition_info
            && addr.index == index
            && addr.location == location;
    }
    bool operator!=(const addr_type& addr) const
    {
        return !(*this == addr);
    }
};

class SymbolTable {
public:
    SymbolTable()
    {
        // add int 0 as the first value
        value_informations.clear();
        value_info_type vit;
        vit.type = VALUE_TYPE_IS_INT;
        vit.value.ivalue = 0;
        value_informations.push_back(vit);
    }
    addr_type install_id(const std::string& id);
    addr_type install_value(int val);
    addr_type install_value(char val);

    void declare_define_variable(int type, addr_type& addr_id, addr_type& addr_value);
    void declare_array(int type, addr_type& addr_id, std::vector<size_t>& array_times);
    void variable_assignment(addr_type& id, addr_type& value);

    int get_int(addr_type& addr);
    char get_char(addr_type& addr);

    void show_addr(addr_type& addr);
    void show_addr_content(addr_type& addr);
    void query(std::string& id);

private:
    // all id will be save in here
    std::vector<std::string> symbols;
    // query information
    std::unordered_map<size_t, addr_type> symbols_relation;
    // all function information will be save in here
    std::vector<func_info_type> func_informations;
    // all value
    std::vector<value_info_type> value_informations;
    // all array
    std::vector<array_info_type> array_informations;
};

#endif

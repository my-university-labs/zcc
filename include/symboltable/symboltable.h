/* author: dongchangzhang */
/* time: Thu 09 Mar 2017 01:59:17 PM CST */

#ifndef SRC_PLUGIN_SYMBOLTABLE_H
#define SRC_PLUGIN_SYMBOLTABLE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#define ST_ID 1000
#define ST_INT 1001
#define ST_FUNC 1002
#define ST_CHAR 1003
#define ST_ARRAY 1004
#define ST_TMPVAL 1005
#define ST_NONE 1006

#define NONE_FLAG 1000000000

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
    size_t index = NONE_FLAG;
    size_t type;
    size_t location = NONE_FLAG;
    addr_type(const addr_type& addr)
    {
        index = addr.index;
        type = addr.type;
        location = addr.location;
    }
    addr_type& operator=(const addr_type& addr)
    {
        index = addr.index;
        type = addr.type;
        location = addr.location;
        return *this;
    }
    bool operator==(const addr_type& addr) const
    {
        return addr.index == index && addr.type == type && addr.location == location;
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
        value_informations.clear();
        value_info_type vit;
        vit.type = ST_INT;
        vit.value.ivalue = 0;
        value_informations.push_back(vit);
    }
    addr_type install_id(const std::string& id);
    addr_type install_value(int val);
    addr_type install_value(char val);

    void id_assagin(int type, addr_type& addr_id, addr_type& addr_value);
    void array_assagin(int type, addr_type& addr_id, std::vector<size_t>& array_times);

    void assign(addr_type& id, addr_type& value);

    int get_int(addr_type& addr);
    char get_char(addr_type& addr);

    void print_addr(addr_type& addr);
    void print_addr_info(addr_type& addr);
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

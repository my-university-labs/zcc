/* author: dongchangzhang */
/* time: Thu 09 Mar 2017 01:59:17 PM CST */

#ifndef SRC_PLUGIN_SYMBOLTABLE_H
#define SRC_PLUGIN_SYMBOLTABLE_H

#include <string>
#include <unordered_map>
#include <vector>

#define ST_FUNC 1003
#define ST_VALUE 1001
#define ST_ARRAY 1002

class SymbolTable {
public:
    // information for value and value definenation
    typedef struct {
        int type;
        union {
            int ivalue;
            float fvalue;
            char cvalue;
        } value;
    } value_info_type;
    // array
    typedef struct {
        size_t array_times;
        int type;
        std::vector<size_t> times_info;
    } array_info_type;
    // function
    typedef struct {
        int return_type;
        size_t arg_times;

    } func_info_type;
    // addr -> how to locate info about id
    typedef struct {
        size_t which;
        size_t where;
    } addr_type;

public:
    SymbolTable() = default;

    void query(std::string& id);

private:
    // all id will be save in here
    std::unordered_map<std::string, addr_type> symboltable;
    // all function information will be save in here
    std::vector<func_info_type> func_informations;
    // all value
    std::vector<value_info_type> value_informations;
    // all array
    std::vector<array_info_type> array_informations;
};
#endif

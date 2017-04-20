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

std::string install_id(const std::string& id);

class SymbolTable {
public:
    typedef struct {
        int type;
        std::string value;
    } value_info_type;
    typedef struct {
        size_t array_times;
        int type;
        std::vector<size_t> times_info;
    } array_info_type;
    typedef struct {
        int return_type;
        size_t arg_times;

    } func_info_type;
    SymbolTable() = default;

    void insert();
    void query(std::string& id);

private:
    // id -> information
    std::unordered_map<std::string, size_t> symboltable;
    std::vector<func_info_type> func_informations;
    std::vector<value_info_type> value_informations;
    std::vector<array_info_type> array_informations;
};
#endif

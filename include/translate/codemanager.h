#ifndef PLUGIN_ADDR_CODES_H
#define PLUGIN_ADDR_CODES_H

#include "code.h"

#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

#define IS_OP 11
#define IS_INT 21
#define IS_CHAR 31
#define IS_FLOAT 41

size_t timer_code_increase();

class CodeManager {

public:
    CodeManager() = default;

    size_t generate_code(int op, addr_type& addr1, addr_type& addr2, SymbolTableManager& stmg);
    size_t generate_code(int op, size_t addr1, addr_type& addr2, SymbolTableManager& stmg);
    size_t generate_code(int op, addr_type& addr1, size_t addr2, SymbolTableManager& stmg);
    size_t generate_code(int op, size_t addr1, size_t addr2, SymbolTableManager& stmg);
    void print_code(size_t id, SymbolTableManager& stmg);

private:
    size_t timer = 0;

    std::vector<size_t> codes;
    std::vector<Code> code_res;
    std::vector<size_t> tmp_values;
    std::unordered_map<size_t, size_t> relation;

    size_t get_timer() { return timer++; }
    addr_type create_tmp_value(size_t code);
};
#endif
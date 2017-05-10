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

#define ARRAY_ASSIGN 200
#define GOTO 201
#define CMP_GOTO 202

size_t timer_code_increase();

class CodeManager {

public:
    CodeManager() = default;

    size_t generate_code(int op, addr_type& addr1, SymbolTableManager& stmg);
    size_t generate_code(int op, addr_type& addr1, addr_type& addr2, addr_type& addr3, SymbolTableManager& stmg);

    size_t generate_code(int op, addr_type& addr1, addr_type& addr2, SymbolTableManager& stmg);
    size_t generate_code(int op, size_t addr1, addr_type& addr2, SymbolTableManager& stmg);
    size_t generate_code(int op, addr_type& addr1, size_t addr2, SymbolTableManager& stmg);
    size_t generate_code(int op, size_t addr1, size_t addr2, SymbolTableManager& stmg);

    size_t generate_tmp_code(int op, addr_type& addr1, SymbolTableManager& stmg);
    size_t generate_tmp_code(int op, addr_type& addr1, addr_type& addr2, addr_type& addr3, SymbolTableManager& stmg);

    void merge_code();

    void gen_all_code(SymbolTableManager& stmg);

    size_t line_nums_now() { return codes.size(); }

    addr_type get_tmp_addr(size_t id);
    void print_code(size_t id, SymbolTableManager& stmg);

private:
    size_t timer = 0;

    std::vector<Code> codes;
    std::vector<Code> codes_tmp;
    std::unordered_map<size_t, size_t> relation;

    size_t get_timer() { return timer++; }
};
#endif
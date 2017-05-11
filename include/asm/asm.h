/* author: dongchangzhang */
/* time: Thu 11 May 2017 06:24:52 PM CST */

#ifndef ASM_H
#define ASM_H
#include "code.h"
#include "symboltable.h"
#include "symboltablemanager.h"

#include <map>
#include <string>
#include <vector>

class AsmCreater {
public:
    AsmCreater() = default;
    AsmCreater(std::vector<Code>& codes, SymbolTableManager& stmg);
    // void create_asm(std::vector<Code>& codes);
    void create_asm(Code& code, SymbolTableManager& stmg);

private:
    std::vector<size_t> block;
    size_t add = 0;
    size_t index = 0;

    void get_basic_block(std::vector<Code>& codes, SymbolTableManager& stmg);
    void calc_use_chain(std::vector<Code>& codes);

    void gen_asm_code_op_ad_ad(int op, addr_type& addr1, addr_type& addr2, SymbolTableManager& stmg);
    void zero_addr(addr_type& addr1, SymbolTableManager& stmg);
};
#endif /* ifndef  */

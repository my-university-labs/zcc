/* author: dongchangzhang */
/* time: Thu Apr 27 20:37:17 2017 */

#include "code.h"
#include "codemanager.h"
#include "unstd.h"
#include <algorithm>

size_t CodeManager::generate_code(int op, addr_type& addr1, SymbolTableManager& stmg)
{
    Code new_code(op, addr1);
    new_code.try_to_calc(stmg);
    codes.push_back(new_code);
    return codes.size() - 1;
}
size_t CodeManager::generate_code(int op, addr_type& addr1, addr_type& addr2, addr_type& addr3, SymbolTableManager& stmg)
{
    Code new_code(op, addr1, addr2, addr3);
    new_code.try_to_calc(stmg);
    codes.push_back(new_code);
    return codes.size() - 1;
}
size_t CodeManager::generate_code(int op, addr_type& addr1, addr_type& addr2, SymbolTableManager& stmg)
{
    Code new_code(op, addr1, addr2);
    new_code.try_to_calc(stmg);
    codes.push_back(new_code);
    return codes.size() - 1;
}
size_t CodeManager::generate_code(int op, size_t addr1, addr_type& addr2, SymbolTableManager& stmg)
{
    addr_type tmp = codes[addr1].get_result();
    return generate_code(op, tmp, addr2, stmg);
}
size_t CodeManager::generate_code(int op, addr_type& addr1, size_t addr2, SymbolTableManager& stmg)
{
    addr_type tmp = codes[addr2].get_result();
    return generate_code(op, addr1, tmp, stmg);
}
size_t CodeManager::generate_code(int op, size_t addr1, size_t addr2, SymbolTableManager& stmg)
{
    addr_type tmp1 = codes[addr1].get_result();
    addr_type tmp2 = codes[addr2].get_result();
    return generate_code(op, tmp1, tmp2, stmg);
}

addr_type CodeManager::get_tmp_addr(size_t id)
{
    if (id < codes.size() && codes[id].check_result()) {
        codes[id].set_result_as_tmp();
        return codes[id].get_result();

    } else {
        addr_type addr;
        addr.type = ADDR_IS_NONE;
        return addr;
    }
}
void CodeManager::print_code(size_t id, SymbolTableManager& stmg)
{
    codes[id].print_code(id, stmg);
}

void CodeManager::gen_all_code(SymbolTableManager& stmg)
{
    for (size_t i = 0; i < codes.size(); ++i) {
        codes[i].print_code(i, stmg);
    }
}

size_t CodeManager::generate_tmp_code(int op, addr_type& addr1, SymbolTableManager& stmg)
{
    Code new_code(op, addr1);
    new_code.try_to_calc(stmg);
    codes_tmp.push_back(new_code);
    return codes_tmp.size() - 1;
}
size_t CodeManager::generate_tmp_code(int op, addr_type& addr1, addr_type& addr2, addr_type& addr3, SymbolTableManager& stmg)
{
    Code new_code(op, addr1, addr2, addr3);
    new_code.try_to_calc(stmg);
    codes_tmp.push_back(new_code);
    return codes_tmp.size() - 1;
}
void CodeManager::merge_code()
{
    for (auto code : codes_tmp) {
        codes.push_back(code);
    }
    codes_tmp.clear();
}
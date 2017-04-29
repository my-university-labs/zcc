/* author: dongchangzhang */
/* time: Thu Apr 27 20:37:17 2017 */

#include "codemanager.h"
#include <algorithm>

size_t CodeManager::generate_code(int op, addr_type& addr1, addr_type& addr2, SymbolTableManager& stmg)
{
    Code new_code(op, addr1, addr2);
    new_code.try_to_calc(stmg);
    auto ret = find(code_res.begin(), code_res.end(), new_code);
    if (ret == code_res.end()) {
        size_t code_index = code_res.size();
        code_res.push_back(new_code);
        codes.push_back(code_index);
        return codes.size() - 1;
    } else {
        size_t loc = ret - code_res.begin();
        codes.push_back(loc);
        return codes.size() - 1;
    }
}
size_t CodeManager::generate_code(int op, size_t addr1, addr_type& addr2, SymbolTableManager& stmg)
{
    addr_type tmp = code_res[addr1].get_result();
    return generate_code(op, tmp, addr2, stmg);
}
size_t CodeManager::generate_code(int op, addr_type& addr1, size_t addr2, SymbolTableManager& stmg)
{
    addr_type tmp = code_res[addr2].get_result();
    return generate_code(op, addr1, tmp, stmg);
}
size_t CodeManager::generate_code(int op, size_t addr1, size_t addr2, SymbolTableManager& stmg)
{
    addr_type tmp1 = code_res[addr1].get_result();
    addr_type tmp2 = code_res[addr2].get_result();
    return generate_code(op, tmp1, tmp2, stmg);
}

void CodeManager::print_code(size_t id, SymbolTableManager& stmg)
{
    code_res[codes[id]].print_code(stmg);
}

addr_type CodeManager::create_tmp_value(size_t code)
{
    return code_res[code].get_result();
}
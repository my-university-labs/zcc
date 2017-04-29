/* author: dongchangzhang */
/* time: Thu Apr 27 20:36:59 2017 */

#include "code.h"
#include "token.h"

void Code::print_code(SymbolTableManager& stmg)
{
    std::cout << get_token_info(op) << " ";
    stmg.print_addr_info(addr1);
    std::cout << " ";
    stmg.print_addr_info(addr2);
    std::cout << std::endl;
}
void Code::try_to_calc(SymbolTableManager& stmg)
{
    if (addr1.type == ST_INT && addr2.type == ST_INT) {
        int r = stmg.get_int(addr1) + stmg.get_int(addr2);
        std::cout << " -- " << r << std::endl;
    }
}
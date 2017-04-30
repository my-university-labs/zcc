/* author: dongchangzhang */
/* time: Thu Apr 27 20:36:59 2017 */

#include "code.h"
#include "token.h"

void Code::print_code(SymbolTableManager& stmg)
{

    std::cout << "---------------- info new ------------" << std::endl;
    if (have_result) {
        stmg.print_addr_info(result);
        std::cout << " = ";
    }
    std::cout << get_token_info(op) << " ";
    stmg.print_addr_info(addr1);
    std::cout << " ";
    stmg.print_addr_info(addr2);
    std::cout << std::endl;
    std::cout << "------------------ code ------------" << std::endl;
    if (have_result) {
        stmg.print_addr(result);
        std::cout << " = ";
    }
    std::cout << get_token_info(op) << " ";
    stmg.print_addr(addr1);
    std::cout << " ";
    stmg.print_addr(addr2);
    std::cout << std::endl;
}
bool Code::try_to_calc(SymbolTableManager& stmg)
{
    // if (addr1.type == ST_INT && addr2.type == ST_INT) {
    //
    //     std::cout << " -- " << r << std::endl;
    // }
    int r;
    have_result = true;
    if (op == MUL) {
        r = stmg.get_int(addr1) * stmg.get_int(addr2);
    } else if (op == DIV) {
        r = stmg.get_int(addr1) / stmg.get_int(addr2);
    } else if (op == ADD) {
        r = stmg.get_int(addr1) + stmg.get_int(addr2);
    } else if (op == SUB) {
        r = stmg.get_int(addr1) - stmg.get_int(addr2);
    } else {
        have_result = false;
    }
    result = stmg.install_value(r);
    return true;
}
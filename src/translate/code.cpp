/* author: dongchangzhang */
/* time: Thu Apr 27 20:36:59 2017 */

#include "code.h"
#include "token.h"

void Code::print_code(size_t id, SymbolTableManager& stmg)
{

    std::cout << "---------------- info new ------------" << std::endl;
    if (have_result) {
        stmg.show_addr_content(result);
        std::cout << " = ";
    }
    std::cout << get_token_info(op) << " ";
    stmg.show_addr_content(addr1);
    std::cout << " ";
    stmg.show_addr_content(addr2);
    std::cout << std::endl;
    std::cout << "------------------ code ------------" << std::endl;
    std::cout << id << "    ";
    if (have_result) {
        stmg.show_addr(result);
        std::cout << " = ";
    }
    std::cout << get_token_info(op) << " ";
    stmg.show_addr(addr1);
    std::cout << " ";
    stmg.show_addr(addr2);
    std::cout << std::endl
              << std::endl;
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
    } else if (op == GT) {
        r = stmg.get_int(addr1) > stmg.get_int(addr2);
    } else if (op == LT) {
        r = stmg.get_int(addr1) < stmg.get_int(addr2);
    } else if (op == EQ) {
        r = stmg.get_int(addr1) == stmg.get_int(addr2);
    } else if (op == NE) {
        r = stmg.get_int(addr1) != stmg.get_int(addr2);
    } else if (op == OR) {
        r = stmg.get_int(addr1) || stmg.get_int(addr2);
    } else if (op == AND) {
        r = stmg.get_int(addr1) && stmg.get_int(addr2);
    } else {
        have_result = false;
    }
    result = stmg.install_value(r);
    return true;
}
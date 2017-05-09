/* author: dongchangzhang */
/* time: Thu Apr 27 20:36:59 2017 */

#include "code.h"
#include "codemanager.h"
#include "token.h"

void Code::print_code(size_t id, SymbolTableManager& stmg)
{
    print_code1(id, stmg);
}

// man can see
void Code::print_code1(size_t id, SymbolTableManager& stmg)
{
    std::cout << id << ":    ";
    if (if_goto) {
        std::cout << "if ";
        stmg.show_addr_content(addr1);
        std::cout << " " << get_token_info(op) << " ";
        stmg.show_addr_content(addr2);
        std::cout << " goto ";
        stmg.show_addr_content(jump);
        std::cout << "    ";
        stmg.show_addr_content(result);
        std::cout << std::endl;
    } else if (op == GOTO) {
        std::cout << "goto ";
        stmg.show_addr_content(addr1);
        std::cout << std::endl;
    } else {
        // show info
        if (have_result) {
            stmg.show_addr_content(result);
            std::cout << " = ";
        }
        stmg.show_addr_content(addr1);
        if (op == ARRAY_ASSIGN)
            std::cout << " = ";
        else
            std::cout << " " << get_token_info(op) << " ";
        stmg.show_addr_content(addr2);
        std::cout << std::endl;
    }
}
// addr
void Code::print_code2(size_t id, SymbolTableManager& stmg)
{
    if (if_goto) {
        std::cout << id << ":    if ";
        stmg.show_addr(addr1);
        std::cout << " " << get_token_info(op) << " ";
        stmg.show_addr(addr2);
        std::cout << " goto ";
        stmg.show_addr(jump);
        std::cout << std::endl;
    } else if (op == GOTO) {
        std::cout << id << ":   goto ";
        stmg.show_addr(addr1);
        std::cout << std::endl;
    } else {
        // show code
        std::cout << id << ":   ";
        if (have_result) {
            stmg.show_addr(result);
            std::cout << " = ";
        }
        stmg.show_addr(addr1);
        if (op == ARRAY_ASSIGN)
            std::cout << " = ";
        else if (op == GOTO)
            std::cout << " goto ";
        else
            std::cout << " " << get_token_info(op) << " ";
        stmg.show_addr(addr2);
        std::cout << std::endl;
    }
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
    } else if (op == ASSIGN) {
        have_result = false;
        stmg.variable_assignment(addr1, addr2);

    } else if (op == ARRAY_ASSIGN) {
        have_result = false;
        stmg.array_assignment(addr1, addr2);

    } else {
        have_result = false;
    }
    result = stmg.install_value(r);
    return true;
}
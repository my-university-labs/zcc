/* author: dongchangzhang */
/* time: Thu 11 May 2017 06:26:02 PM CST */
#include "asm.h"
#include "token.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

#define CMP 1000
#define MOV 1001
#define TEST 1002

std::map<int, std::string> lables{
    { ADD, "ADD" },
    { MUL, "MUL" },
    { SUB, "SUB" },
    { DIV, "DIV" },
    { CMP, "CMP" },
    { MOV, "MOV" },
    { TEST, "TEST" },
    { OR, "OR" }
};
AsmCreater::AsmCreater(std::vector<Code>& codes, SymbolTableManager& stmg)
{
    //get_basic_block(codes, stmg);
    for (size_t i = 0; i < codes.size(); ++i) {
        create_asm(codes[i], stmg);
    }
}
void AsmCreater::get_basic_block(std::vector<Code>& codes, SymbolTableManager& stmg)
{
    std::cout << "Asm -> " << codes.size() << std::endl;
    // the first code
    block.push_back(0);
    for (size_t i = 0; i < codes.size(); ++i) {
        if (codes[i].is_goto()) {
            // where can goto
            size_t where = codes[i].goto_where(stmg);
            if (find(block.begin(), block.end(), where) == block.end()) {
                block.push_back(where);
            }
            if (find(block.begin(), block.end(), where + 1) == block.end()) {
                block.push_back(where + 1);
            }
        }
    }
    sort(block.begin(), block.end());
}
void AsmCreater::create_asm(Code& code, SymbolTableManager& stmg)
{
    int op = code.get_op();

    auto addr1 = code.get_addr1();
    auto addr2 = code.get_addr2();
    auto addr3 = code.get_result();
    if (code.is_goto()) {
        std::cout << std::left << std::setw(5) << index++ << "    ";
        std::cout << "JMP " << code.goto_where(stmg) + add << std::endl;
    } else if (code.is_if_goto() && op != AND && op != OR) {
        gen_asm_code_op_ad_ad(CMP, addr1, addr2, stmg);
        std::cout << std::left << std::setw(5) << index++ << "    ";
        ++add;
        std::cout << "CJ " << get_token_info(code.get_op()) << " " << code.goto_where(stmg) + add << std::endl;
    } else {

        switch (op) {
        case ASSIGN:
            gen_asm_code_op_ad_ad(MOV, addr2, addr1, stmg);
            break;
        case ADD:
            zero_addr(addr3, stmg);
            ++add;
            gen_asm_code_op_ad_ad(MOV, addr1, addr3, stmg);
            ++add;
            gen_asm_code_op_ad_ad(op, addr2, addr3, stmg);
            break;
        case MUL:
            zero_addr(addr3, stmg);
            ++add;
            gen_asm_code_op_ad_ad(MOV, addr1, addr3, stmg);
            ++add;
            gen_asm_code_op_ad_ad(op, addr2, addr3, stmg);
            break;
        case DIV:
            zero_addr(addr3, stmg);
            ++add;
            gen_asm_code_op_ad_ad(MOV, addr1, addr3, stmg);
            ++add;
            gen_asm_code_op_ad_ad(op, addr2, addr3, stmg);
            break;
        case SUB:
            zero_addr(addr3, stmg);
            ++add;
            gen_asm_code_op_ad_ad(MOV, addr1, addr3, stmg);
            ++add;
            gen_asm_code_op_ad_ad(op, addr2, addr3, stmg);
            break;
        case AND:
            gen_asm_code_op_ad_ad(TEST, addr1, addr2, stmg);
            std::cout << std::left << std::setw(5) << index++ << "    ";
            ++add;
            std::cout << "JNZ " << code.goto_where(stmg) + add << std::endl;
            break;
        case OR:
            gen_asm_code_op_ad_ad(OR, addr1, addr2, stmg);
            std::cout << std::left << std::setw(5) << index++ << "    ";
            ++add;

            std::cout << "JNZ " << code.goto_where(stmg) + add << std::endl;
            break;
        }
    }
}
void AsmCreater::gen_asm_code_op_ad_ad(int op, addr_type& addr1, addr_type& addr2, SymbolTableManager& stmg)
{
    std::cout << std::left << std::setw(5) << index++ << "    ";

    std::cout << lables[op] << " ";
    stmg.show_addr_content(addr1);
    std::cout << ", ";
    stmg.show_addr_content(addr2);
    std::cout << std::endl;
}
void AsmCreater::zero_addr(addr_type& addr1, SymbolTableManager& stmg)
{
    std::cout << std::left << std::setw(5) << index++ << "    ";

    std::cout << "MOV   0";
    std::cout << ", ";
    stmg.show_addr_content(addr1);
    std::cout << std::endl;
}

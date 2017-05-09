#ifndef PLUGIN_CODE_H
#define PLUGIN_CODE_H

#include "symboltablemanager.h"
#include <iostream>

// one addr use addr1
class Code {
public:
    Code() = default;
    Code(int p, addr_type& ad1)
        : op(p)
        , addr1(ad1)
    {
    }
    Code(int p, addr_type& ad1, addr_type& ad2)
        : op(p)
        , addr1(ad1)
        , addr2(ad2)
    {
    }
    Code(int p, addr_type& ad1, addr_type& ad2, addr_type& ad3)
        : op(p)
        , addr1(ad1)
        , addr2(ad2)
        , jump(ad3)
        , if_goto(true)
    {
    }
    void print_code(size_t id, SymbolTableManager& stmg);
    void print_code1(size_t id, SymbolTableManager& stmg);
    void print_code2(size_t id, SymbolTableManager& stmg);

    bool operator==(const Code& code) const
    {
        return (code.op == op
            && code.addr1 == addr1
            && code.addr2 == addr2);
    }
    bool operator!=(const Code& code) const
    {
        return !(*this == code);
    }
    addr_type get_result() { return result; }

    bool try_to_calc(SymbolTableManager& stmg);

    bool check_result() { return have_result; }

private:
    int op;
    addr_type addr1;
    addr_type addr2;
    addr_type result;
    addr_type jump;
    int addition_info;
    bool have_result = false;
    bool if_goto = false;
    friend std::ostream& operator<<(std::ostream& os, const Code& code);
};

#endif
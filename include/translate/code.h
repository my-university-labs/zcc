#ifndef PLUGIN_CODE_H
#define PLUGIN_CODE_H

#include "symboltablemanager.h"
#include <iostream>

class Code {
public:
    Code() = default;
    Code(int p, addr_type& ad1, addr_type& ad2, size_t i)
        : op(p)
        , addr1(ad1)
        , addr2(ad2)
        , id(id)
    {
        result.type = ST_TMPVAL;
    }
    void print_code(SymbolTableManager& stmg);

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

    void try_to_calc(SymbolTableManager& stmg);

private:
    int op;
    addr_type addr1;
    addr_type addr2;
    addr_type result;
    size_t id;
    friend std::ostream& operator<<(std::ostream& os, const Code& code);
};

#endif
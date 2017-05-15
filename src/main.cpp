/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:42:23 PM CST */

#include "asm.h"
#include "error.h"
#include "parser.h"
#include "translate.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        print_error(-1, -1, NONE_INPUT);
        return 1;
    }

    std::cout << "--------------- 3 addr code --------------------" << std::endl;
    Parser parser(argv[1], argv[2], argv[3]);
    parser.run();
    auto codes = parser.get_codes();
    auto stmg = parser.get_stmg();
    std::cout << "-------------------- Asm ------------------------" << std::endl;

    AsmCreater asm_creater(codes, stmg);

    return 0;
}

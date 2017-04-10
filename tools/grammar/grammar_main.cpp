/* author: dongchangzhang */
/* time: Sun 02 Apr 2017 12:43:58 PM CST */

#include "error.h"
#include "grammar_tool.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        print_error(-1, -1, NO_GRAMMAR);
    }

    GrammarDealer dealer(argv[1]);
    dealer.run();

    return 0;
}

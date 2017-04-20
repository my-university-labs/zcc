/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:42:23 PM CST */

#include "error.h"
#include "parser.h"
#include "translate.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

void test_lex(std::string file);

int main(int argc, char* argv[])
{
    if (argc == 1) {
        print_error(-1, -1, NONE_INPUT);
        return 1;
    }
    Parser parser(argv[1], argv[2], argv[3]);
    parser.run();

    return 0;
}

/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:42:23 PM CST */

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#include "zerror.h"
#include "LexicalAnalyzer.h"

int main(int argc, char* argv[])
{
    if (argc == 1) {
       print_error(-1, NONE_INPUT); 
       return 1;
    }
    





    // sadffsada
    LexicalAnalyzer a(argv[1]);
    a.analyze();
    return 0;
}

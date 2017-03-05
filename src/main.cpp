/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:42:23 PM CST */

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

#include "LexicalAnalyzer.h"

int main()
{
    LexicalAnalyzer a("test.c");
    a.preprocess();
    return 0;
}

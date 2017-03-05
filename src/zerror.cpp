/* author: dongchangzhang */
/* time: Sun 05 Mar 2017 12:25:06 PM CST */

#include <iostream>
#include <string>

#include "zerror.h"


const std::vector<std::string> zerrormsg {
    "need a input file written by c language",
    "illegal name",
    "divided by zero",

};

void print_error(int linenu, int id) {
    std::cout << "error: ";
    if (linenu == -1)
        std::cout << zerrormsg[id] << std::endl;
    else
        std::cout << "line " << linenu << " : " << zerrormsg[id] << std::endl;
}

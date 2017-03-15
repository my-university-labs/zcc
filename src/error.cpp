/* author: dongchangzhang */
/* time: Sun 05 Mar 2017 12:25:06 PM CST */

#include <iostream>
#include <string>

#include "error.h"


const std::vector<std::string> zerrormsg {
    "program error: not define symbol",
    "need a input file written by c language",
    "illegal name",
    "divided by zero",
    "need end symbol */ for comment, please check"

};

void print_error(int linenu, int id, std::string info) {
    std::cout << "error: ";
    if (linenu == -1)
        std::cout << zerrormsg[id] << " " << info << std::endl;
    else
        std::cout << "line " 
            << linenu << " : " 
            << zerrormsg[id] 
            << " " << info << std::endl;
}

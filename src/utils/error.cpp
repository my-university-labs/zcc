/* author: dongchangzhang */
/* time: Sun 05 Mar 2017 12:25:06 PM CST */

#include "error.h"

#include <iostream>
#include <string>



const std::vector<std::string> zerrormsg {
    "program error: not define symbol",
    "need a input file written by c language",
    "illegal name",
    "divided by zero",
    "need end symbol */ for comment, please check",
    "is a number you want? i can not recognize it",
    "must start with a lilegal char",
    "need ' but not found",
    "need \" but not found",

};

void print_error(int linenu, int index,  int id, std::string info) {
    std::cout << "error: ";
    if (linenu == -1)
        std::cerr << zerrormsg[id] << " " << info << std::endl;
    else
        std::cerr << "LINE: " 
            << linenu << "->" << index << " \"" 
            << info << "\" MSG:"
            << zerrormsg[id] << std::endl;
}

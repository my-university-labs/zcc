/* author: dongchangzhang */
/* time: Sun 05 Mar 2017 12:25:06 PM CST */

#include "error.h"

#include <iostream>

const std::map<int, std::string> zerrormsg{
    { NONE_DEFINE_SYMBOL, "program error: not define symbol" },
    { NONE_INPUT, "need a input file written by c language" },
    { ILLEGAL_NAME, "illegal name" },
    { DIVIDE_ZERO, "divided by zero" },
    { COMMENT_NOT_END, "need end symbol */ for comment, please check" },
    { ILLEGAL_NUM, "is a number you want? i can not recognize it" },
    { BAD_START_CHAR, "must start with a lilegal char" },
    { LACK_SQUOTE, "need ' but not found" },
    { LACK_DQUOTE, "need \" but not found" },
    { NO_GRAMMAR, "need a grammar file" },

};

void print_error(int linenu, int index, int id, std::string info)
{
    std::cout << "error: ";
    if (linenu == -1)
        std::cerr << zerrormsg.at(id) << " " << info << std::endl;
    else
        std::cerr << "LINE: "
                  << linenu << "->" << index << " \""
                  << info << "\" MSG:"
                  << zerrormsg.at(id) << std::endl;
}

void print_error(int id)
{
    print_error(-1, -1, id, "");
}

/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:42:23 PM CST */

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "utils.h"
#include "error.h"
#include "token.h"
#include "tokenizer.h"

int main(int argc, char* argv[])
{
    if (argc == 1) {
       print_error(-1, -1,  NONE_INPUT); 
       return 1;
    }
    
    Tokenizer a(argv[1]);

    int i = 0;
    while (!a.isend()) {
        Token v = a.next();
        if (v.get_token() != -1) {
            std::string token = "<" + std::to_string(v.get_token()) + ", " + v.get_attr() + ">"; 
        std::cout << "token   "<< std::setw(5) << i << "  at line  " <<  std::setw(5) 
            <<  a.get_linenu() << "  is "<< std::setw(30)<< token << "    should be: ";
        if (v.get_token() != ID && v.get_token() != VALUE) std::cout << get_token_info(v.get_token()) << std::endl;
        else std::cout << v.get_attr() << std::endl;
        ++i;

    }}
    return 0;
}

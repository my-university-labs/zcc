/* author: dongchangzhang */
/* time: Wed 22 Mar 2017 11:18:19 PM CST */

#include "grammerdealer.h"

#include <iostream>
#include <string>

bool GrammerDealer::load_grammer() {
    std::string line;
    std::string element;
    std::cout << "start to load the grammer" << std::endl;
    std::cout << file << std::endl;

    while (std::getline(in, line)) {
        std::cout << line << std:: endl;
    }
    return true;
}

/* author: dongchangzhang */
/* time: Mon 27 Mar 2017 07:36:17 PM CST */

#include "grammar.h"

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>


void Grammar::insert(std::string &key, std::string &comment) {
    std::string element;
    std::vector<std::string>> tmp;
    std::istringstream in(comment);
    while (in >> element) {
        tmp.push_back(element);
    }
    if (grammar.find(key) != grammar.end()) {
        grammar[key].push_back(tmp);
    }
    else { 
        std::vector<std::vector<std::string>> vtmp{tmp}; grammar[key] = vtmp;
    }
}


std::vector<Element> Grammar::get_content(std::string &key) {
    if (grammar.find(key) != grammar.end()) return grammar[key];
    return std::vector<Element> ();
}

void Grammar::check()
{
    for (auto &v : grammar) {
        std::cout << "->" << v.first << std::endl;
        for (auto &e : v.second) {
            for (auto &i : e.get_elements()) {
                std::cout << "  " << i;
            }
            std::cout << std::endl;
        }
    }
}

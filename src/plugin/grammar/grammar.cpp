/* author: dongchangzhang */
/* time: Mon 27 Mar 2017 07:36:17 PM CST */

#include "grammar.h"

#include <iostream>
#include <map>
#include <vector>
#include <string>


void Grammar::insert(std::string &key, Element &element) {
    if (grammar.find(key) != grammar.end()) grammar[key].push_back(element);
    else { std::vector<Element> tmp{element}; grammar[key] = tmp;}
}


std::vector<Element> Grammar::get_elements(std::string &key) {
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

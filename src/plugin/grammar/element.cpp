/* author: dongchangzhang */
/* time: Mon 27 Mar 2017 07:18:53 PM CST */

#include "element.h"

#include <string>
#include <vector>
#include <sstream>

Element::Element(std::string &pa, std::string &value)
{
    parent = pa;
    std::string word;
    std::istringstream in(value);
    while (in >> word) {
        element.push_back(word);
    }

}

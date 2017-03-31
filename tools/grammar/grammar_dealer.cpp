/* author: dongchangzhang */
/* time: Wed 22 Mar 2017 11:18:19 PM CST */

#include "grammar_dealer.h"

#include <iostream>
#include <string>
#include <sstream>

#include "grammar.h"
#include "element.h"

bool GrammerDealer::load_grammer() {
    std::string start, line, key, value, comment;

    while (std::getline(in, line)) {
        if (line.size() > 0) {
            std::istringstream in(line);
            in >> start;

            if (start == "#") ; // is comment, do nothing now
            else if (start == "->") { in >> key; }
            else {
                Element element(key, line);
                grammar.insert(key, element);
            }
        }
    }
//    grammar.check();
    return true;
}

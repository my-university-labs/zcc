/* author: dongchangzhang */
/* time: Mon 27 Mar 2017 07:30:04 PM CST */
#ifndef SRC_PLUGIN_GRAMMER_H
#define SRC_PLUGIN_GRAMMER_H

#include "element.h"

#include <string>
#include <map>
#include <vector>

class Grammar {
    public:
        Grammar() {}
        void insert(std::string &key, Element &element);

        std::vector<Element> get_elements(std::string &key);

        void check();

    private:
        std::map<std::string, std::vector<Element>> grammar;
};
#endif

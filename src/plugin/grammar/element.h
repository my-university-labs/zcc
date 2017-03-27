/* author: dongchangzhang */
/* time: Mon 27 Mar 2017 07:10:41 PM CST */

#ifndef SRC_PLUGIN_GRA_ELEMENT_H
#define SRC_PLUGIN_GRA_ELEMENT_H

#include <string>
#include <vector>

class Element {
    public:
        Element(std::string &pa, std::string &value);
        Element(std::string &pa, std::string &value, std::string &com) : comment(com) { Element(pa, value); }

        int get_dot_location() { return dot_location; }
        std::vector<std::string> get_elements() { return element;  }


    private:
        int dot_location = 0;
        std::string comment;
        std::string parent;

        std::vector<std::string> element;
};
#endif /* ifndef SSRC_PLUGIN_GRA_ELEMENT_H
} */

/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 11:43:53 PM CST */
#ifndef TOOLS_GRAMMAR_STATUS_H
#define TOOLS_GRAMMAR_STATUS_H

#include "item.h"
#include <vector>

class Status {
    public:
        Status();

        std::vector<Item> get_content() const { return content; }

        void add_item(Item &item) { content.push_back(Item); }

    private:
        std::vector<Item> content;
        // wait;
};
#endif

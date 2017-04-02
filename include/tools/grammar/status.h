/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 11:43:53 PM CST */

// used to save every status of dfa

#ifndef TOOLS_GRAMMAR_STATUS_H
#define TOOLS_GRAMMAR_STATUS_H

#include "item.h"
#include <vector>
#include <algorithm>

class Status {
public:
    Status() {}

    std::vector<Item> get_content() const { return content; }

    void add_item(Item &item) { content.push_back(item); }

    Status& operator+=(const Status &status) {
        for (auto s : status.content) {
            if (find(content.begin(), content.end(), s) == content.end()) {
                content.push_back(s);
            }
        }
        return *this;
    }

    bool operator==(const Status &status) const {
        return content == status.content;
    }

private:
    std::vector<Item> content;
    // wait;
};
#endif

/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 11:43:53 PM CST */

// used to save every status of dfa

#ifndef TOOLS_GRAMMAR_STATUS_H
#define TOOLS_GRAMMAR_STATUS_H

#include "item.h"

#include <algorithm>
#include <unordered_set>

class Status {
public:
    Status() {}

    std::unordered_set<Item> get_content() const { return content; }

    void add_item(Item& item);

    Status& operator+=(const Status& status);

    bool operator==(const Status& status) const;

    inline size_t size() { return content.size(); }

private:
    std::unordered_set<Item> content;
    // wait;
};
#endif

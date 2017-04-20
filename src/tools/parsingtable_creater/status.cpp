/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 11:52:45 PM CST */

#include "status.h"

#include <iostream>

void Status::add_item(Item& item)
{
    content.insert(item);
}

Status& Status::operator+=(const Status& status)
{
    for (auto item : status.content) {
        content.insert(item);
    }
    return *this;
}
bool Status::operator==(const Status& status) const
{
    bool equal = true;
    if (content.size() == status.content.size()) {
        for (auto item : status.content) {
            if (content.find(item) == content.end()) {
                equal = false;
                break;
            }
        }
    } else {
        equal = false;
    }
    return equal;
}
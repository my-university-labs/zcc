/* author: dongchangzhang */
/* time: Thu 30 Mar 2017 11:32:53 PM CST */
#ifndef SRC_PLUGIN_GRAMMAR_H
#define SRC_PLUGIN_GRAMMAR_H

#include <string>

struct Item {
    Item();
    /* which production */
    int which;
    /* the content of the production */
    int content;
    /* decimal before location */
    int decimal_location;
    /* end symbols */
    // -----
    
    std::string next();
};

#endif

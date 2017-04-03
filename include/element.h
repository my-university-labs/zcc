/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 09:33:22 AM CST */

// A class used to save grammar item such as A -> abCDEd...

#ifndef SRC_PARSER_ELEMENT_H
#define SRC_PARSER_ELEMENT_H

#include "token.h"

#include <string>
#include <vector>

class Element {
public:
    Element(const std::string& w, const std::string& c);

private:
    Token which;
    std::vector<Token> content;
};
#endif /* ifndef SSRC_PARSER_ELEMENT_H */

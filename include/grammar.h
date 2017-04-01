/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 12:09:31 AM CST */

#ifndef SRC_PARSER_GRAMMAR_H
#define SRC_PARSER_GRAMMAR_H

#include "token.h"
#include <string>

class Grammar {
    public:
        // input a grammar file
        Grammar(std::string grammarf);
    private:
        void load_grammar();
        // how to save grammar


};
#endif

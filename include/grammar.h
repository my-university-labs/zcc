/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 12:09:31 AM CST */

#ifndef SRC_PARSER_GRAMMAR_H
#define SRC_PARSER_GRAMMAR_H

#include "token.h"
#include <string>
#include <vector>
#include <map>

class Grammar {
public:
    // input a grammar file
    // the grammar file format is:
    // -> start symbol
    //  production1
    //  production2
    //  ...
    // -> start symbol2
    //  production1
    //  production2
    //  ...
    Grammar(std::string grammarf);

    std::vector<Token> get_production(const std::string &which, size_t id) const;

    void check_grammar();

    std::vector<Token> get_special_state() {
        return get_production(start_state, 0);
    }
private:
    std::string start_state;

    // grammar saver
    // key -> [production1, production2 ...]
    std::map<Token, std::vector<std::vector<Token>>> grammar;
};
#endif

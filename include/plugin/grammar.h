/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 12:09:31 AM CST */

#ifndef SRC_PARSER_GRAMMAR_H
#define SRC_PARSER_GRAMMAR_H

#include "token.h"

#include <map>
#include <string>
#include <vector>

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

    std::vector<Token> get_production(const std::string& which, size_t id) const;

    std::vector<std::vector<Token> > get_production(const Token& token) const;

    void check_grammar();

    std::vector<Token> get_special_state() const
    {
        return get_production(start_state, start_index);
    }
    std::string get_start_state() const { return start_state; }

    size_t get_start_index() const { return start_index; }

    size_t get_start_size() const { return get_special_state().size(); }
private:
    std::string start_state;

    size_t start_index = 0;
    // grammar saver
    // key -> [production1, production2 ...]
    std::map<Token, std::vector<std::vector<Token> > > grammar;
};
#endif

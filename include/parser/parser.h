/* author: dongchangzhang */
/* time: Sat 11 Mar 2017 11:24:49 PM CST */

#ifndef SRC_PARSER_PARSER_H
#define SRC_PARSER_PARSER_H

#include "grammar.h"
#include "parsing_table.h"
#include "symboltable.h"
#include "token.h"
#include "tokenizer.h"
#include "translate.h"

#include <iostream>
#include <map>
#include <stack>
#include <vector>
class Parser {
public:
    friend class Translater;
    typedef struct {
        int type;
        std::string svol;
        int ivol;
        float fvol;
        size_t index;
        std::vector<addr_type> array_times;
        addr_type addr;

    } vol_type;
    Parser() = default;
    Parser(std::string grammarf, std::string tablef, std::string sourcef)
        : grammar(grammarf)
        , ptable(tablef)
        , tokenizer(sourcef)
    {
    }

    void init();
    // run parser
    void run();

    void hook_function(std::string& which, size_t& index, int linenu);

private:
    // grammar
    Grammar grammar;
    // parsing table
    ParsingTable ptable;

    SymbolTableManager smanager;

    Tokenizer tokenizer;

    Translater translater;
    // stack to save state and input token
    std::stack<Token> token_stack;

    std::stack<size_t> status_stack;

    std::stack<vol_type> vol_stack;

    void deal_error(int linenu, size_t cursor, const std::string& line, std::map<int, std::string> next_token_should_be);
    void print_production(std::string& which, size_t& index, int linenu);
};
std::ostream& operator<<(std::ostream& os, Parser::vol_type& vol);

#endif

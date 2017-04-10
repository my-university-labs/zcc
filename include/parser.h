/* author: dongchangzhang */
/* time: Sat 11 Mar 2017 11:24:49 PM CST */

#ifndef SRC_PARSER_PARSER_H
#define SRC_PARSER_PARSER_H

#include "grammar.h"
#include "parsing_table.h"
#include "token.h"
#include "tokenizer.h"

#include <map>
#include <stack>

class Parser {
public:
    Parser(std::string grammarf, std::string tablef, std::string sourcef)
        : grammar(grammarf)
        , ptable(tablef)
        , tokenizer(sourcef)
    {
    }

    void init();
    // run parser
    void run();

    void hook_function(std::string& which, size_t& index, const std::vector<Token>& tokens, int linenu);

private:
    // grammar
    Grammar grammar;
    // parsing table
    ParsingTable ptable;
    // tokenizer
    Tokenizer tokenizer;
    // stack to save state and input token
    std::stack<Token> token_stack;

    std::stack<size_t> status_stack;

    void deal_error(int linenu, size_t cursor, const std::string& line, std::map<int, std::string> next_token_should_be);
};

#endif

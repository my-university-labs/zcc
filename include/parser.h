/* author: dongchangzhang */
/* time: Sat 11 Mar 2017 11:24:49 PM CST */

#ifndef SRC_PARSER_PARSER_H
#define SRC_PARSER_PARSER_H

#include "grammar.h"
#include "parsing_table.h"
#include "token.h"
#include "tokenizer.h"

#include <stack>

class Parser {
public:
    Parser(std::string sourcef, std::string grammarf, std::string tablef)
        : grammar(grammarf)
        , ptable(tablef)
        , tokenizer(sourcef)
    {
    }
    // run parser
    void run();

private:
    // grammar
    Grammar grammar;
    // parsing table
    ParsingTable ptable;
    // tokenizer
    Tokenizer tokenizer;
    // stack to save state and input token
    std::stack<Token> pstack;
};

#endif

/* author: dongchangzhang */
/* time: Sat 11 Mar 2017 11:24:09 PM CST */
#include "parser.h"
#include "token.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void Parser::run()
{
    Token token = tokenizer.next();
    std::cout << token.get_token() << std::endl;
    token = tokenizer.next();
    std::cout << token.get_token() << std::endl;
    token = tokenizer.next();
    std::cout << token.get_token() << std::endl;
    token = tokenizer.next();
    std::cout << token.get_token() << std::endl;

    // grammar.check_grammar();

    std::string which = "function_declare";
    std::vector<Token> r = grammar.get_production(which, 0);
    for (auto t : r) {
        std::cout << t.get_token() << " " << t.get_attr() << " | ";
    }
    std::cout << std::endl;
}

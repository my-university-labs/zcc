/* author: dongchangzhang */
/* time: Sat 11 Mar 2017 11:24:09 PM CST */
#include "parser.h"
#include "token.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void Parser::init()
{
    while (!token_stack.empty())
        token_stack.pop();
    while (!status_stack.empty())
        status_stack.pop();

    std::cout << grammar.get_start_state() << std::endl;
    Token start_token(grammar.get_start_state());
    token_stack.push(start_token);
    std::cout << ptable.get_default_start_state() << std::endl;
    status_stack.push(ptable.get_default_start_state());
}
void Parser::run()
{
    init();
    // Token token = tokenizer.next();
    // std::cout << token.get_token() << std::endl;
    // token = tokenizer.next();
    // std::cout << token.get_token() << std::endl;
    // token = tokenizer.next();
    // std::cout << token.get_token() << std::endl;
    // token = tokenizer.next();
    // std::cout << token.get_token() << std::endl;

    // // grammar.check_grammar();

    // std::string which = "function_declare";
    // std::vector<Token> r = grammar.get_production(which, 0);
    // for (auto t : r) {
    //     std::cout << t.get_token() << " " << t.get_attr() << " | ";
    // }
    // std::cout << std::endl;
    // ptable.output_action_table();
    // ptable.output_goto_table();
}

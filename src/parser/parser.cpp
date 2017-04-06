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
    // clear stack
    while (!token_stack.empty())
        token_stack.pop();
    while (!status_stack.empty())
        status_stack.pop();
    // null symbol
    Token start_token;
    token_stack.push(start_token);
    // start state default 0
    status_stack.push(ptable.get_default_start_state());
}
void Parser::run()
{
    init();
    while (true) {
        Token token_now = tokenizer.next();

        if (tokenizer.is_end())
            break;
        std::cout << token_now.get_token() << " " << token_now.get_attr() << std::endl;
        size_t status_now = status_stack.top();
        if (!token_now.is_state_token()) {
            auto action = ptable.query_action(status_now, token_now.get_token());
            if (action.error) {
                // deal error;
                std::cerr << "error action" << std::endl;
                exit(3);
            } else if (action.action == MOVE_IN) {
                status_stack.push(action.next_status);
                token_stack.push(token_now);
            } else if (action.action == REDUCTION) {
                auto production = grammar.get_production(action.which, action.index);
                for (size_t i = 0; i < production.size(); ++i) {
                    token_stack.pop();
                    status_stack.pop();
                }
                token_stack.push(Token(action.which));
            } else {
                // deal error
            }
        } else {
            auto togo = ptable.query_goto(status_now, token_now);
            if (togo.error) {
                // deal error
                std::cerr << "error goto" << std::endl;
            } else {
                status_stack.push(togo.next_status);
            }
        }
    }
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

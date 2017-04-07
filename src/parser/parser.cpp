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

    // grammar.check_grammar();
}
void Parser::run()
{
    init();
    Token token_now = tokenizer.next();

    while (true) {
        std::cout << token_now.get_token() << " " << token_now.get_attr() << std::endl;
        size_t status_now = status_stack.top();
        std::cout << "Status: " << status_stack.top() << std::endl;
        // if (!token_now.is_state_token()) {
        auto action = ptable.query_action(status_now, token_now.get_token());
        std::cout << "Action: " << action.error << " " << action.action << " " << action.next_status << " " << action.which << " " << action.index << std::endl;
        if (action.error) {
            // deal error;
            std::cerr << "error action" << std::endl;
            exit(3);
        } else if (action.action == MOVE_IN) {
            std::cout << MOVE_IN << " " << token_now.get_token() << std::endl;
            status_stack.push(action.next_status);
            token_stack.push(token_now);
            token_now = tokenizer.next();
        } else if (action.action == REDUCTION) {
            std::cout << REDUCTION << " " << action.which << std::endl;
            std::cout << action.index << std::endl;
            auto production = grammar.get_production(action.which, action.index);
            for (size_t i = 0; i < production.size(); ++i) {
                token_stack.pop();
                status_stack.pop();
            }
            auto status_new = status_stack.top();
            auto togo0 = ptable.query_goto(status_new, Token(action.which));
            token_stack.push(Token(action.which));
            status_stack.push(togo0.next_status);
            hook_function(action.which, action.index, production);

        } else if (action.action == ACCEPT) {
            std::cout << "fuck accept" << std::endl;
            exit(0);
        } else {
            std::cerr << "terminate" << std::endl;
        }
        // } else {
        //     // auto togo = ptable.query_goto(status_now, token_now);
        //     // std::cout << "GoTo: " << togo.error << " " << togo.next_status << std::endl;
        //     // if (togo.error) {
        //     //     // deal error
        //     //     std::cerr << "error goto" << std::endl;
        //     // } else {
        //     //     status_stack.push(togo.next_status);
        //     // }
        // }
        // if (tokenizer.is_end())
        //     break;
    }
}

void Parser::hook_function(std::string& which, size_t& index, const std::vector<Token>& tokens)
{
    std::cout << "HOOK start" << std::endl;
    std::cout << which << " -> ";

    for (auto t : tokens) {
        if (t.is_state_token()) {
            std::cout << 1 << std::endl;
            std::cout << t.get_state();
        } else if (t.is_null_token()) {
            std::cout << "#";
        } else if (t.is_id()) {
            std::cout << t.get_state() << std::endl;
        } else {
            std::cout << get_token_info(t.get_token());
        }
        std::cout << " ";
    }
    std::cout << "HOOK end"
              << std::endl;
}
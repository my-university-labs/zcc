/* author: dongchangzhang */
/* time: Sat 11 Mar 2017 11:24:09 PM CST */
#include "parser.h"

#include <algorithm>
#include <iomanip>
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
    while (!vol_stack.empty())
        vol_stack.pop();
    // null symbol
    Token start_token;
    token_stack.push(start_token);
    // start state default 0
    status_stack.push(ptable.get_default_start_state());
}
void Parser::run()
{
    init();
    Token token_now = tokenizer.next();
    Token last_token = token_now;
    while (true) {
        size_t status_now = status_stack.top();
        auto action = ptable.query_action(status_now, token_now.get_token());
        if (action.error) {
            // deal error;
            deal_error(tokenizer.get_linenu(), tokenizer.get_cursor(),
                tokenizer.get_line(), action.next_token_should_be);
            std::cerr << "error action at line :" << tokenizer.get_linenu()
                      << std::endl;
            std::cerr << "input token is : <" << token_now.get_token() << ", "
                      << token_now.get_attr() << ">" << std::endl;
            exit(3);
        } else if (action.action == MOVE_IN) {
            status_stack.push(action.next_status);
            token_stack.push(token_now);
            token_now = tokenizer.next();
        } else if (action.action == REDUCTION) {
            hook_function(action.which, action.index, tokenizer.get_linenu());
        } else if (action.action == ACCEPT) {
            std::cout << "\nFUCK ACCEPT" << std::endl;
            exit(0);
        } else {
            std::cerr << "terminate" << std::endl;
            exit(1);
        }
    }
}
void Parser::hook_function(std::string& which, size_t& index, int linenu)
{
    std::cout << "___" << std::endl;
    std::string action = grammar.get_action(which, index);
    translater.action_run(*this, action, which, index);
    // auto production = grammar.get_production(which, index);
    // // pop
    // for (size_t i = 0; i < production.size(); ++i) {
    //     token_stack.pop();
    //     status_stack.pop();
    // }
    // push
    auto status_new = status_stack.top();
    auto togo0 = ptable.query_goto(status_new, Token(which));
    token_stack.push(Token(which));
    status_stack.push(togo0.next_status);
    print_production(which, index, linenu);
}
void Parser::print_production(std::string& which, size_t& index, int linenu)
{
    auto tokens = grammar.get_production(which, index);
    std::cout << std::left << std::setw(5) << linenu
              << which << "  ->  ";
    for (auto t : tokens) {
        if (t.is_state_token()) {
            std::cout << t.get_state();
        } else if (t.is_null_token()) {
            std::cout << "#";
        } else if (t.is_id()) {
            std::cout << t.get_state();
        } else {
            std::cout << get_token_info(t.get_token());
        }
        std::cout << "    ";
    }
    std::cout << std::endl;
}
void Parser::deal_error(int linenu, size_t cursor, const std::string& line,
    std::map<int, std::string> next_token_should_be)
{
    std::cout << std::endl;
    std::cout << "Shit Error At " << linenu << " : " << std::endl;
    std::cout << line << std::endl;
    std::cout << std::string(cursor, ' ') << "^" << std::endl;
    std::cout << "try :" << std::endl;
    for (auto action : next_token_should_be) {

        if (action.first == ID) {
            std::cout << "could be: ID" << std::endl;
        } else if (action.first == VALUE) {
            std::cout << "could be: VALUE" << std::endl;
        } else if (action.first >= 21) {
            std::cout << "could be: " << get_token_info(action.first) << std::endl;
        }
    }
    std::cout << std::endl;
}
std::ostream& operator<<(std::ostream& os, Parser::vol_type& vol)
{
    if (vol.type == VOL_IS_VALUE_TYPE)
        os << vol.ivol;
    else if (vol.type == VOL_IS_ID)
        os << vol.svol;
    else if (vol.type == VOL_IS_NUM_VALUE)
        os << vol.svol;
    else
        os << "VOL_ERROR" << std::endl;
    return os;
}
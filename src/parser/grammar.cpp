/* author: dongchangzhang */
/* time: Sat 01 Apr 2017 12:10:03 AM CST */

#include "grammar.h"
#include "error.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

Grammar::Grammar(std::string grammarf)
{
    int code;
    bool first_which = true;
    std::ifstream in(grammarf);
    if (!in) {
        print_error(NO_GRAMMAR);
        exit(1);
    }
    std::string which;
    std::string start, comment, line;
    std::vector<Token> ptmp;
    std::vector<std::vector<Token> > productions;
    while (std::getline(in, line)) {
        std::istringstream is(line);
        is >> start;
        if (start == "->") {
            is >> which;
            if (first_which) {
                start_state = which;
                first_which = false;
            }
        } else if (start == "#") {
            comment = line;
        } else if (start != "") {
            ptmp.clear();
            while (true) {
                if (start == "identity") {
                    // id
                    Token token(ID, start);
                    ptmp.push_back(token);
                } else if (start == "value") {
                    // value
                    Token token(VALUE, start);
                    ptmp.push_back(token);
                } else if (start == "null") {
                    Token token;
                    ptmp.push_back(token);
                } else if ((code = get_code(start)) != ID) {
                    // key word, separator or operator
                    Token token(code, start);
                    ptmp.push_back(token);
                } else {
                    // state
                    Token token(start);
                    ptmp.push_back(token);
                }
                if (!(is >> start))
                    break;
            }
            Token parent(which);
            if (grammar.find(parent) != grammar.end()) {
                grammar[parent].push_back(ptmp);
            } else {
                productions.clear();
                productions.push_back(ptmp);
                grammar[parent] = productions;
            }
        }
    }
}

void Grammar::check_grammar()
{
    for (auto& p : grammar) {
        // which
        std::cout << (p.first).get_state() << std::endl;
        for (auto& v1 : p.second) {
            // production
            for (auto e : v1) {
                std::cout << e.get_token() << " " << e.get_attr() << "    ";
            }
            std::cout << std::endl;
        }
        std::cout << " ---------- " << std::endl;
    }
}

std::vector<Token> Grammar::get_production(const std::string& which, size_t id) const
{
    Token parent(which);
    if (grammar.find(parent) != grammar.end() && grammar.at(parent).size() > id) {
        return grammar.at(parent).at(id);
    } else {
        std::cout << "not find grammar 1 at grammar.cpp : " << which << " " << id << std::endl;
        std::vector<Token> tmp;
        return tmp;
    }
}

std::vector<std::vector<Token> > Grammar::get_production(const Token& token) const
{

    if (grammar.find(token) != grammar.end()) {
        return grammar.at(token);
    } else {
        std::cout << "not find grammar 2 at grammar.cpp : " << token.get_state() << std::endl;
        std::vector<std::vector<Token> > tmp;
        return tmp;
    }
}

/* author: dongchangzhang */
/* time: Thu 09 Mar 2017 10:42:31 AM CST */

#ifndef INCLUDE_UTILS_H
#define INCLUDE_UTILS_H

#include <string>

struct Token {
    int token;
    std::string value;

    Token() : token(-1), value("") {}
    Token(int t) : token(t), value("") {}
    Token(int t, std::string v) : token(t), value(v) {}
    int get_token() { return token; }
    std::string get_attr() { return value; }
    void put_token(int t) { token = t; }
    void put_attr(std::string &v) { value = v; }
};

#endif

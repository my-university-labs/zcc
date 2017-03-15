/* author: dongchangzhang */
/* time: Thu 09 Mar 2017 10:42:31 AM CST */

#ifndef __UTILS_H__
#define __UTILS_H__

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

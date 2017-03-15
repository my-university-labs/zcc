/* author: dongchangzhang */
/* time: Wed 08 Mar 2017 04:05:31 PM CST */

#include <iostream>
#include <string>
#include <array>
#include <cctype>

#include "token.h"
#include "error.h"

const std::array<std::string, TOKEN_SIZE> token_dict {
    "id", // 0
    "int", // 1
    "float", // 2
    "double", // 3
    "long", // 4
    "short", // 5
    "switch", // 6
    "case", // 7
    "default", // 8
    "break", // 9
    "const", // 10
    "return", // 11
    "void", // 12
    "continue", // 13
    "do", // 14
    "while", // 15
    "if", // 16
    "else", // 17
    "for", // 18
    "char", // 19
    "typedef", // 20
    "static", // 21
    "==", // 22
    "!=", // 23
    ">", // 24
    "<", // 25
    ">=", // 26
    "<=", // 27
    "=", // 28
    "+", // 29
    "*", // 30
    "-", // 31
    "/", // 32
    "!", // 33
    "%", // 34
    "&&", // 35
    "||", // 36
    "+=", // 37
    "-=", // 38
    "*=", // 39
    "/=", // 40
    ",", // 41
    "(", // 42
    ")", // 43
    "[", // 44
    "]", // 45
    "{", // 46
    "}", // 47
    ";", // 48
    "\\", // 49
    "'", // 50
    "\"", // 51
};


bool is_good(const std::string &target) {
    if (isdigit(target[0])) return false;
    for (size_t i = 1; i < target.size(); ++i) {
        if (!isalnum(target[i]) && target[i] != '-') {
            return false;

    }}
    return true;
}

std::string get_token_info(const int id) {
    if (id < 0 || id >= TOKEN_SIZE) 
        print_error(-1, 1);
    return token_dict[id];
}

int get_code(const std::string &target) {
    for (int i = 1; i < TOKEN_SIZE; ++i) {
        if (token_dict[i] == target)
            return i;
    }
    if (!is_good(target)) return -1;
    return 0;
}

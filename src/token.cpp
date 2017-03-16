/* author: dongchangzhang */
/* time: Wed 08 Mar 2017 04:05:31 PM CST */

#include <iostream>
#include <string>
#include <map>
#include <cctype>

#include "token.h"
#include "error.h"

const std::map<std::string, int> token_dict {
    {"int", INT},
    {"float", FLOAT},
    {"double", DOUBLE},
    {"long", LONG},
    {"short", SHORT},
    {"switch", SWITCH},
    {"case", CASE},
    {"default", DEFAULT},
    {"break", BREAK},
    {"const", CONST},
    {"return", RETURN},
    {"void", VOID},
    {"continue", CONTINUE},
    {"do", DO},
    {"while", WHILE},
    {"if", IF},
    {"else", ELSE},
    {"for", FOR},
    {"char", CHAR},
    {"typedef", TYPEDEF},
    {"static", STATIC},
    {"==", EQ},
    {"!=", NE},
    {">", GT},
    {"<", LT},
    {">=", GE},
    {"<=", LE},
    {"=", ASSIGN},
    {"+", ADD},
    {"*", MUL},
    {"-", SUB},
    {"/", DIV},
    {"!", NOT},
    {"%", MOD},
    {"&&", AND},
    {"||", OR},
    {"+=", ADDASSIGN},
    {"-=", SUBASSIGN},
    {"*=", MULASSIGN},
    {"/=", DIVASSIGN},
    {",", COMMA},
    {"(", LCURVES},
    {")", RCURVES},
    {"[", LBRACKET},
    {"]", RBRACKET},
    {"{", LBRACE},
    {"}", RBRACE},
    {";", SEM},
    {"\\", REVERSE},
    {"'", SQUOTE},
    {"\"", DQUOTE},
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
    for (auto m : token_dict) {
        if (m.second == id) {
            return m.first;
        }
    }
    return "";
}

int get_code(const std::string &target) {
    auto it = token_dict.find(target);
    if (it != token_dict.end())
        return it->second;
    return ID;
}

bool issymbol(char X) {
    switch (X) {
        case '+': case '-': case '*': case '/':
        case '=': case '%': case '&': case '|':
        case '(': case ')': case '[': case ']':
        case '{': case '}': case ';': case ':':
        case '\'': case '"': return true;
        default: return false;
    }
}

/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:40:02 PM CST */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <map>
#include <set>

#include "zerror.h"
#include "LexicalAnalyzer.h"

const std::unordered_map<std::string, int> keyword_table {
    {"int", 11},
    {"float", 12},
    {"double", 13},
    {"char", 14},
    {"if", 15},
    {"else", 16},
    {"while", 17},
    {"for", 18},
    {"return", 19},
    {"void", 20},
    {"const", 21}
};

const std::unordered_map<std::string, int> operator_table {
    {"+", 101},
    {"-", 102},
    {"*", 103},
    {"/", 104},
    {"=", 105},
    {"%", 106},
    {"++", 107},
    {"--", 108},
    {"+=", 109},
    {"-=", 110},
    {"*=", 111},
    {"/=", 112},
    {"==", 113},
    {"->", 115},
    {"||", 116},
    {"&&", 117},
    {">", 118},
    {"<", 120},
    {">=", 121},
    {"<=", 122},
    {"<<", 123},
    {">>", 124},
};
const std::unordered_map<std::string, int> sepatator_table {
    {"{", 201},
    {"}", 202},
    {";", 203},
    {"\"", 204},
    {"'", 205},
    {"//", 206},
    {"/*", 207},
    {"*/", 208},
};
const std::vector<std::string> token_table{
    "id",  // value id
    "num", // number
    "if",  // key word
    "else"
    "while"
    "int",
    "float",
    "double",
    "char",
    "+",
    "-",
    "*",
    "/",
    "%",
};

void LexicalAnalyzer::analyze() {

}


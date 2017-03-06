/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:40:02 PM CST */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <regex>
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
    int linenu = 0;
    // regex
    std::regex re(pattern);
    std::smatch result;
    std::string elements;
    // open file
    std::ifstream in;
    in.open(file);
    // read elements
    std::string line;
    // get line
    while (getline(in, line)) {
        ++linenu;
        std::istringstream is(line);
        while (is >> elements) {
            while (elements != "") {
                bool isfind = std::regex_search(elements, result, re);

                if (isfind) {
                    std::string element = result.str();
                    if (element != "//" && element != "/*")
                        deal_element(result.str());
                    else if (element == "//")
                        break;
                    else
                        ignore_comment(linenu, elements, in);

                }
                else
                    print_error(-1, NONE_DEFINE_SYMBOL, elements);
                elements = result.suffix();
            }
        }
    }
    in.close();
}

void LexicalAnalyzer::deal_element(const std::string element) {
    std::cout << element << std::endl;
    if (is_operator(element)) {
        std::cout << " is operator" << std::endl;
    }
    else if (is_keyword(element)) {
        std::cout << " is key word" << std::endl;
    }
    else if (is_separator(element)) {
        std::cout << " is sepatator" << std::endl;
    }
    
}

std::ifstream&
LexicalAnalyzer::ignore_comment(int &linenu, const std::string &elements, std::ifstream& in) {
    char x;
    std::string line;

    std::istringstream is(elements);
    while (is.get(x)) {
        std::cout << x << std::endl;
    }


    return in;
}

bool LexicalAnalyzer::is_keyword(const std::string& s) {
    auto r = keyword_table.find(s);
    if (r != keyword_table.cend()) return true;
    return false;
}
bool LexicalAnalyzer::is_separator(const std::string& s) {
    auto r = sepatator_table.find(s);
    if (r != sepatator_table.cend()) return true;
    return false;
}
bool LexicalAnalyzer::is_value(const std::string &s) {
    return false;
}
bool LexicalAnalyzer::is_operator(const std::string& s) {
    auto r = operator_table.find(s);
    if (r != operator_table.cend()) return true;
    return false;
}


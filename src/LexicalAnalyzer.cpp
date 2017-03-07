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
#include <cctype>
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
    {"(", 125},
    {")", 126},
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
    std::regex re_comment_end(comment_end);
    std::smatch result;
    std::string elements;
    // open file
    std::ifstream in;
    in.open(file);
    // read elements
    std::string line;
    bool jumpout = false;
    // get line
    while (getline(in, line)) {
        ++linenu;
        std::istringstream is(line);
        while (is >> elements) {
            while (elements != "") {
                bool isfind = std::regex_search(elements, result, re);
                if (isfind) {
                    std::string element = result.str();
                    if (element == "'" || element == "\"") {
                        elements = result.suffix();
                        get_value(linenu, element, elements, in, is);
                        continue;
                    }

                    else if (element == "//") {
                        jumpout = true;
                        break;
                    }
                    
                    else if (element == "/*"){
                        ignore_comment(linenu, elements, re_comment_end, in, is);
                        continue;
                    }
                    else 
                        deal_element(element);
                }
                else
                    print_error(-1, NONE_DEFINE_SYMBOL, elements);
                elements = result.suffix();
            }
            if (jumpout) {
                jumpout = false;
                break;
            }
        }
    }
    in.close();
}

void LexicalAnalyzer::print_token() {
    for (auto &vs : token_result) {
        bool first = true;
        std::cout << "<";
        for (auto v : vs) {
            if (first) first = false;
            else std::cout <<", ";
            std::cout << v;
        }
        std::cout << ">" << std::endl;
    }
}
void LexicalAnalyzer::deal_element(const std::string element) {
    std::vector<std::string> token_element;

    if (is_operator(element)) {
        token_element.push_back(std::to_string(WT_OPERATOR));
    }
    else if (is_keyword(element)) {
        token_element.push_back(std::to_string(WT_KEYWORD));
    }
    else if (is_separator(element)) {
        token_element.push_back(std::to_string(WT_SEPARATOR));
    }
    else if (is_value(element)) {
        token_element.push_back(std::to_string(WT_VALUE));
    }
    else if (!check_identifier(element)) {
        print_error(-1,1);
    }
    else {
        token_element.push_back(std::to_string(WT_IDENTIFIER));
    }

    token_element.push_back(element);
    token_result.push_back(token_element);
    
}

void LexicalAnalyzer::ignore_comment(int &linenu, 
        std::string &elements, std::regex &re, 
        std::ifstream& in, std::istringstream &is) {
    std::smatch result;
    std::cout << "comment " << linenu << " " << elements << std::endl;
    do {
        bool isfind = std::regex_search(elements, result, re);
        if (isfind) {
            elements = result.suffix();
            return;
        }
    } while (is >> elements);

    std::string line;
    while (getline(in, line)) {
        ++linenu;
        bool isfind = std::regex_search(line, result, re);
        if (isfind) {
            elements = "";
            is.str(result.suffix());
            return;
        }
    }
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
    for (auto ch : s) {
        if (ch < '0' || ch > '9')
            return false;
    }
    return true;
}

bool LexicalAnalyzer::is_operator(const std::string& s) {
    auto r = operator_table.find(s);
    if (r != operator_table.cend()) return true;
    return false;
}

bool LexicalAnalyzer::check_identifier(const std::string &s) {
    if (s[0] >= '0' && s[0] <= '9') return false;
    for (auto ch : s) {
        if (!std::isalnum(ch) && ch != '_') {
            return false;
        }
    }
    return true;
}


void LexicalAnalyzer::get_value(
        int &linenu,
        const std::string &sp,
        std::string &elements, 
        std::ifstream &in,
        std::istringstream &is) {

    std::string result = sp;
    char flag;
    if (sp == "'") flag = '\'';
    else flag = '"';

    for (size_t i = 0; i < elements.size(); ++i) {
        result += elements[i];
        if (elements[i] == flag) {
            elements = elements.substr(i + 1, elements.size() - i - 1);
            insert_value(result);
            return;
        }
    }
    char x;
    elements = "";
    while (is.get(x)) {
        result += x;
        if (x == flag) {
            insert_value(result);
            return;
        }
    }
    is.str("");
    std::string line;
    while (getline(in, line)) {
        ++linenu;
        for (size_t i = 0; i < line.size(); ++i) {
            result += line[i];
            if (line[i] == flag) {
                is.str(line.substr(i + 1, elements.size() - i - 1));
                insert_value(result);
                std::cout << result << std::endl;
                return;
            }
        }
    }
}

void LexicalAnalyzer::insert_value(const std::string &s) {
    std::vector<std::string> tmp;
    tmp.push_back(std::to_string(WT_VALUE));
    tmp.push_back(s);
    token_result.push_back(tmp);
    
}

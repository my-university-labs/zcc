/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:40:02 PM CST */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <cctype>
#include <map>
#include <set>

#include "LexicalAnalyzer.h"
#include "SymbolTable.h"
#include "token.h"
#include "zerror.h"

void LexicalAnalyzer::skip_ws() {
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {
            line.erase(0, i);
            break;
        } 
    }
}

void LexicalAnalyzer::ignore_comment() {
    std::cout << "# log: skip comment" << std::endl;
    std::smatch outcome;
    do {
        bool feedback = std::regex_search(line, outcome, re_comment_end);
        if (feedback) {
            line = outcome.suffix();
            break;
        }
    } while (getline(in, line));

}

ZToken LexicalAnalyzer::get_ch() {
    std::string r = "'";
    if (line[1] == '\'') {
        r += line[0];
        r + "'";
        line.erase(0, 2);
    }
    ZToken z(VALUE, r);
    return z;
}

ZToken LexicalAnalyzer::get_string() {
    std::string r = "";
    bool okay = false;
    do {
        okay =false;
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '"') {
                okay = true;
                r += line.substr(0, i);
                line.erase(0, i + 1);
                break;
            }
        }
        if (!okay) r += line;
        else break;
    } while(getline(in, line));

    ZToken z(VALUE, r);
    return z;
}
ZToken LexicalAnalyzer::next() {
    if (line == "") {
        if (getline(in, line)) {
            ;
        }
        else {
            finished = true;
            ZToken z;
            return z;
        }
    }
    return do_next();
}

ZToken LexicalAnalyzer::deal_element(const std::string& element) {
    std::cout << element << std::endl;
    // std::cout << "# log: input element -> " <<  element << std::endl;
    if (std::regex_match(element, re_number)) {
        // std::cout << "# log : element " << element << " is digit" << std::endl;
        ZToken z(VALUE, element);
        return z;
    } 
    else {
        int code = get_code(element);
        // std::cout << "# log: token is -> " << code << std::endl;
        // std::cout << "# log: check token -> " << code << " should be " << get_token_info(code) << std::endl;
        ZToken z(code);
        if (code == ID) {
            std::string addr = install_id(element);
            z.put_attr(addr);
        }
        return z;
    }
}
ZToken LexicalAnalyzer::do_next() {
    // result
    ZToken result;
    // re match result
    std::smatch outcome;
    // skip white char
    skip_ws();
    if (line == "") return next();
    bool isfind = std::regex_search(line, outcome, re_pattern);
    if (isfind) {
        std::string element = outcome.str();
        if (element == "'") {
            line = outcome.suffix();
            // find the char or string in this function
            // after find ,return;
            return get_ch(); // should be func
        }
        else if (element == "\"") {
            line = outcome.suffix();
            return get_string();
        }
        else if (element == "//") {
            // skip comments and then find again;
            // func of ignore_comment
            line = "";
            return next();
        }
        else if (element == "/*"){
            ignore_comment();
            // ignore_comment(linenu, elements, re_comment_end, in, is);
            return do_next();
        }
        else {
            line = outcome.suffix();
            // may be an element, deal it
            return deal_element(element);
        }
    }
    else {
        // not find, there is an error 
        // deal error here
        print_error(-1, NONE_DEFINE_SYMBOL, line);
        line.erase(0, 1);
        return result;
    }
}

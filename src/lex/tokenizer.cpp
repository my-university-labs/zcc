/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:40:02 PM CST */


#include "tokenizer.h"
#include "symboltable.h"
#include "token.h"
#include "error.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>


void Tokenizer::skip_ws() {
    for (; cursor < buffer_size; ++cursor)
        if (!isspace(buffer[cursor])) break;
}

void Tokenizer::skip_annotation() {

    while (true){
        if (cursor == 0) {
            ++cursor;
            continue;
        }
        if (cursor >= buffer_size) {
            check_buffer();
            continue;
        }
        if (buffer[cursor - 1] == '*' && buffer[cursor] == '/') {
            ++cursor;
            break;
        }
        ++cursor;
    }

}

void Tokenizer::check_buffer() {
    skip_ws();
    while (buffer_size == 0 || cursor >= buffer_size) {
        // std::cout << buffer_size << " " << cursor << std::endl;
        /* read a now line */
        if (!getline(in, buffer)) {
            finished = true;
            // wait for ....
            exit(1);
        }
        ++linenu;
        cursor = 0;
        buffer_size = buffer.size();
        skip_ws();
    }
}

void Tokenizer::deal_word(std::vector<char> &vtoken, bool &reidentify) {
    char ch;
    while (cursor < buffer_size) {
        ch = buffer[cursor];
        if (isalnum(ch) || ch == '_') {
            vtoken.push_back(ch);
        }
        else if (issymbol(ch) || isspace(ch)) {
            break;
        }
        else {
            deal_error(ILLEGAL_NAME, reidentify);
            break;
        }
        ++cursor;
    }
}

void Tokenizer::deal_num(std::vector<char> &vtoken, bool &reidentify) {
    char ch;
    while (cursor < buffer_size) {
        ch = buffer[cursor];
        if (isdigit(ch)) {
            vtoken.push_back(ch);
        }
        else if (issymbol(ch) || isspace(ch)) {
            break;
        }
        else {
            deal_error(ILLEGAL_NUM, reidentify);
            break;
        }
        ++cursor;
    }
}
void Tokenizer::deal_symbol(std::vector<char> &vtoken, bool &reidentify) {
    char nextch;
    char last = vtoken[0];
    bool have_two = (cursor + 1 < buffer_size && issymbol(buffer[cursor]));
    if (have_two) nextch = buffer[cursor];
    switch (last) {
    case '=':
        if (have_two && nextch == '=') {
            vtoken.push_back(nextch);
            ++cursor;
        }
        break;
    case '+':
        if (have_two) {
            switch (nextch) {
            case '=': vtoken.push_back(nextch); ++cursor; break;
            case '+': vtoken.push_back(nextch); ++cursor; break;
            }
        }
        break;
    case '-':
        if (have_two)
            switch (nextch) {
            case '-': vtoken.push_back(nextch); ++cursor; break;
            case '=': vtoken.push_back(nextch); ++cursor; break;

            }
        break;
    case '*':
        if (have_two) {
            if (nextch == '=') { vtoken.push_back(nextch); ++cursor; }
        }
        break;
    case '/':
        if (have_two) {
            switch (nextch) {
            case '=': vtoken.push_back(nextch); ++cursor; break;
            case '*': vtoken.clear(); ++cursor; skip_annotation(); reidentify = true; break;
            case '/': vtoken.clear(); cursor = buffer_size; reidentify = true; break;
            }
        }
        break;
    case '%':
        if (have_two) { 
            if (nextch == '=') { vtoken.push_back(nextch); ++cursor; }
        }
        break;
    case '&':
        if (have_two) {
            if (nextch == '&') { vtoken.push_back(nextch); ++cursor; }
        }
        break;
    case '|':
        if (have_two) {
            if (nextch == '|') { vtoken.push_back(nextch); ++cursor; }
        }
        break;
    case '\'':
        ++cursor;
        vtoken.clear();
        if (nextch == '\'') return;
        else {
            if (buffer[cursor] == '\'') {
                vtoken.push_back(nextch);
                ++cursor;
            }
            else {
                deal_error(LACK_SQUOTE, reidentify);
            }
        }
        break;
    }

}

void Tokenizer::deal_error(int error_type, bool &reidentify) {
    reidentify = true;
    print_error(linenu, cursor, error_type, buffer);
}

void iswhat(std::string &stoken) {
}
Token Tokenizer::next() {
    char ch;
    int rtype = 0;
    Token token;
    bool reidentify = false;
    check_buffer();
    std::vector<char> vtoken;
    ch = buffer[cursor++];
    vtoken.push_back(ch);
    if (isalpha(ch)) {
        /* a-zA-Z */
        deal_word(vtoken, reidentify);
        if (!reidentify) rtype = 1;
    }
    else if (isdigit(ch)) {
        /* 0-9 */
        deal_num(vtoken, reidentify);
        if (!reidentify) rtype = 2;
    }
    else if(issymbol(ch)){
        /* symbol such as: +-*/
        deal_symbol(vtoken, reidentify);
        if (!reidentify) rtype = 3;
    }
    else {
        /* error start symbol */
        deal_error(BAD_START_CHAR, reidentify);
    }
    if (finished) {
        return token;
    }
    else if (reidentify) {
        // std::cout << "re identify " << std::endl;
        return next();
    }
    else {
        /* return */
        std::string stoken(vtoken.begin(), vtoken.end());
#ifndef NOLOG
        std::cout << "# LOG-> " << stoken << std::endl;
#endif
        if (rtype == 1 || rtype == 3) { 
            if (stoken == "") {
                token.put_token(VALUE);
                token.put_attr(stoken);
                return token;
            }
            int code = get_code(stoken);
            token.put_token(code);
            if (code == ID) {
                std::string addr = install_id(stoken);
                token.put_attr(addr);
            }
        }
        else if (rtype == 2) { token.put_token(VALUE); token.put_attr(stoken);}

        return token;
    }
}




/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:40:02 PM CST */

#include "tokenizer.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#include "error.h"
#include "symboltable.h"
#include "token.h"

/* skip space char */
void Tokenizer::skip_ws()
{
    for (; cursor < buffer_size; ++cursor)
        if (!isspace(buffer[cursor]))
            break;
}
/* skip comments like this one */
void Tokenizer::skip_annotation()
{

    while (true) {
        /* end lables must have two chars, one is * another is/ */
        if (cursor == 0) {
            ++cursor;
            continue;
        }
        /* walk to the end of the line but not find end lable, so read a new line */
        if (cursor >= buffer_size) {
            check_buffer();
            continue;
        }
        /* judge it */
        if (buffer[cursor - 1] == '*' && buffer[cursor] == '/') {
            ++cursor;
            break;
        }
        /* get next char */
        ++cursor;
    }
}
/* skip space, if walk to end, read a new line */
void Tokenizer::check_buffer()
{
    skip_ws();
    while (buffer_size == 0 || cursor >= buffer_size) {
        /* read a now line */
        if (!getline(in, buffer)) {
            buffer_size = 0;
            finished = true;
            return;
        }
        ++linenu;
        cursor = 0;
        buffer_size = buffer.size();
        skip_ws();
    }
}
/* deal key word or id */
void Tokenizer::deal_word(std::vector<char>& vtoken, bool& reidentify)
{
    char ch;
    while (cursor < buffer_size) {
        ch = buffer[cursor];
        if (isalnum(ch) || ch == '_') {
            vtoken.push_back(ch);
        }
        /* end */
        else if (issymbol(ch) || isspace(ch)) {
            break;
        }
        /* meet error */
        else {
            deal_error(ILLEGAL_NAME, reidentify);
            break;
        }
        ++cursor;
    }
}
/* deal num */
void Tokenizer::deal_num(std::vector<char>& vtoken, bool& reidentify)
{
    char ch;
    bool have_dot = false;
    while (cursor < buffer_size) {
        ch = buffer[cursor];
        if (isdigit(ch)) {
            vtoken.push_back(ch);
        } else if (ch == '.' && !have_dot) {
            vtoken.push_back(ch);
            have_dot = true;
        } else if (issymbol(ch) || isspace(ch)) {
            break;
        } else {
            deal_error(ILLEGAL_NUM, reidentify);
            break;
        }
        ++cursor;
    }
}
/* deal operator or separaters */
void Tokenizer::deal_symbol(std::vector<char>& vtoken, bool& reidentify, bool& is_value)
{
    char nextch;
    char last = vtoken[0];
    bool have_two = (cursor + 1 < buffer_size && issymbol(buffer[cursor]));
    if (have_two)
        nextch = buffer[cursor];
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
            case '=':
                vtoken.push_back(nextch);
                ++cursor;
                break;
            case '+':
                vtoken.push_back(nextch);
                ++cursor;
                break;
            }
        }
        break;
    case '-':
        if (have_two)
            switch (nextch) {
            case '-':
                vtoken.push_back(nextch);
                ++cursor;
                break;
            case '=':
                vtoken.push_back(nextch);
                ++cursor;
                break;
            }
        break;
    case '*':
        if (have_two) {
            if (nextch == '=') {
                vtoken.push_back(nextch);
                ++cursor;
            }
        }
        break;
    case '/':
        if (have_two) {
            switch (nextch) {
            case '=':
                vtoken.push_back(nextch);
                ++cursor;
                break;
            case '*':
                vtoken.clear();
                ++cursor;
                skip_annotation();
                reidentify = true;
                break;
            case '/':
                vtoken.clear();
                cursor = buffer_size;
                reidentify = true;
                break;
            }
        }
        break;
    case '%':
        if (have_two) {
            if (nextch == '=') {
                vtoken.push_back(nextch);
                ++cursor;
            }
        }
        break;
    case '&':
        if (have_two) {
            if (nextch == '&') {
                vtoken.push_back(nextch);
                ++cursor;
            }
        }
        break;
    case '|':
        if (have_two) {
            if (nextch == '|') {
                vtoken.push_back(nextch);
                ++cursor;
            }
        }
        break;
    case '\'':
        ++cursor;
        vtoken.clear();
        is_value = true;
        /* char '' */
        if (nextch == '\'')
            return;
        else {
            /* char '?' */
            if (buffer[cursor] == '\'') {
                vtoken.push_back(nextch);
                ++cursor;
            } else {
                deal_error(LACK_SQUOTE, reidentify);
            }
        }
        break;
    }
}

void Tokenizer::deal_error(int error_type, bool& reidentify)
{
    reidentify = true;
    print_error(linenu, cursor, error_type, buffer);
}

Token Tokenizer::next()
{
    char ch;
    int rtype = 0;
    bool is_value = false;
    bool reidentify = false;
    check_buffer();
    if (buffer_size == 0)
        return token;
    std::vector<char> vtoken;
    ch = buffer[cursor++];
    vtoken.push_back(ch);
    if (isalpha(ch) || ch == '_') {
        /* a-zA-Z_ */
        deal_word(vtoken, reidentify);
        if (!reidentify)
            rtype = 1;
    } else if (isdigit(ch)) {
        /* 0-9 */
        deal_num(vtoken, reidentify);
        if (!reidentify)
            rtype = 2;
    } else if (issymbol(ch)) {
        /* symbol such as: +-*/
        deal_symbol(vtoken, reidentify, is_value);
        if (!reidentify)
            rtype = 3;
    } else {
        /* error start symbol */
        deal_error(BAD_START_CHAR, reidentify);
    }
    if (finished) {
        Token token;
        return token;
    } else if (reidentify) {
        // std::cout << "re identify " << std::endl;
        return next();
    } else {
        /* return */
        std::string stoken(vtoken.begin(), vtoken.end());
#ifndef NOLOG
        std::cout << "# LOG-> " << stoken << std::endl;
#endif
        if (rtype == 1 || rtype == 3) {
            // is char
            if (is_value) {
                Token(VALUE, stoken);
                return token;
            }
            // operator separator or key word
            int code = get_code(stoken);
            Token token(code, stoken);
            return token;
        }
        // is value
        else if (rtype == 2) {
            Token token(VALUE, stoken);
            return token;
        } else {
            // no use now
            Token token;
            return token;
        }
    }
}

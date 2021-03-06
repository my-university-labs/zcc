/* author: dongchangzhang */
/* time: Wed 08 Mar 2017 03:35:41 PM CST */

#ifndef SRC_LEX_TOKEN_H
#define SRC_LEX_TOKEN_H

// id
#define ID 0

// key words
#define INT 1 // int
#define FLOAT 2 // float
#define DOUBLE 3 // double
#define LONG 4 // long
#define SHORT 5 // short
#define SWITCH 6 // switch
#define CASE 7 // case
#define DEFAULT 8 // default
#define BREAK 9 // break
#define CONST 10 // const
#define RETURN 11 // return
#define VOID 12 // void
#define CONTINUE 13 // continue
#define DO 14 // do
#define WHILE 15 // while
#define IF 16 // if
#define ELSE 17 // else
#define FOR 18 // for
#define CHAR 19 // char
#define TYPEDEF 20 // typedef
#define STATIC 21 // static

// operator
#define EQ 22 // ==
#define NE 23 // !=
#define GT 24 // >
#define LT 25 // <
#define GE 26 // >=
#define LE 27 // <=
#define ASSIGN 28 // =
#define ADD 29 // +
#define MUL 30 // *
#define SUB 31 // -
#define DIV 32 // /
#define NOT 33 // !
#define MOD 34 // %
#define AND 35 // &&
#define OR 36 // ||
#define ADDASSIGN 37 // +=
#define SUBASSIGN 38 // -=
#define MULASSIGN 39 // *=
#define DIVASSIGN 40 // /=
#define COMMA 41 // ,
#define LCURVES 42 // (
#define RCURVES 43 // )
#define LBRACKET 44 // [
#define RBRACKET 45 // ]

// separators
#define LBRACE 46 // {
#define RBRACE 47 // }
#define SEM 48 // ;
#define REVERSE 49 // '\\'
#define SQUOTE 50 // '
#define DQUOTE 51 // "
#define ADDADD 52 // ++
#define SUBSUB 53 // --
#define MAO 54 // :

#define VALUE 100

#include "symboltable.h"
#include "unstd.h"

#include <map>
#include <string>
#include <vector>

extern const std::map<std::string, int> token_dict;

bool issymbol(char X);

std::string get_token_info(const int id);

int get_code(const std::string& target);

class Token {
public:
    // null token
    Token()
        : token(NULL_STATE)
        , value("null")
        , is_state(false)
        , is_null(true)
    {
    }
    // key world
    Token(int t, std::string v)
        : token(t)
        , value(v)
        , is_state(false)
        , is_null(false)
    {
    }
    // value && id
    Token(int t, addr_type& addr)
        : token(t)
        , addr(addr)
        , is_state(false)
        , is_null(false)
    {
    }
    // state token
    Token(std::string state)
        : token(NORMAL_STATE)
        , value(state)
        , is_state(true)
        , is_null(false)
    {
    }
    Token(int t)
        : Token(t, "")
    {
    }

    Token& operator=(const Token& t)
    {
        this->token = t.token;
        this->value = t.value;
        this->is_state = t.is_state;
        this->is_null = t.is_null;
        this->addr = t.addr;
        return *this;
    }

    bool operator<(const Token& t) const { return (value < t.value); }

    bool operator>(const Token& t) const { return (value > t.value); }

    bool operator==(const Token& t) const { return value == t.value; }

    bool operator==(const int i) const { return token == i; }

    bool operator==(const std::string& s) const { return value == s; }

    int get_token() const { return token; }

    std::string get_attr() const { return value; }

    std::string get_state() const { return value; }

    addr_type get_addr() const
    {
        if (token == ID || token == VALUE)
            return addr;
        else
            std::cerr << "terminal - token";
        exit(0);
    }

    bool is_null_token() const { return is_null; }

    bool is_state_token() const { return is_state; }

    bool is_id() const { return (token == ID ? true : false); }

    bool is_value() const { return (token == VALUE ? true : false); }

    void set_as_end() { token = END_STATE; }

    void show_addr() { std::cout << "from token.h " << addr.type << " " << addr.index << " " << addr.location << std::endl; }

private:
    // token id
    int token;
    // token attr
    addr_type addr;

    std::string value;
    // is state or not
    bool is_state = false;
    // a null token ?
    bool is_null = false;
};

// overwrite hash<token>
namespace std {
template <>
struct hash<Token> {
    typedef size_t return_type;
    typedef Token argument_type;
    size_t operator()(const Token& t) const
    {
        return hash<string>()(t.get_attr()) ^ hash<int>()(t.get_token());
    };
};
}

std::ostream& operator<<(std::ostream& os, Token& token);
#endif

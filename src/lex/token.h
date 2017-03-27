/* author: dongchangzhang */
/* time: Wed 08 Mar 2017 03:35:41 PM CST */

#ifndef SRC_LEX_TOKEN_H
#define SRC_LEX_TOKEN_H

// id
#define ID 0

// key words
#define INT 1   // int
#define FLOAT 2 // float
#define DOUBLE 3 // double
#define LONG 4 // long
#define SHORT 5 // short
#define SWITCH 6 //switch
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

#define VALUE 100

#include <string>
#include <map>


extern const std::map<std::string, int> token_dict;

bool issymbol(char X);

std::string get_token_info(const int id);

int get_code(const std::string &target);

#endif

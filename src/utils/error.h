/* author: dongchangzhang */
/* time: Sun 05 Mar 2017 12:00:59 PM CST */

#ifndef SRC_UTILS_ZERROR_H
#define SRC_UTILS_ZERROR_H

#include <string>
#include <vector>


// error id
#define NONE_DEFINE_SYMBOL 0
#define NONE_INPUT    1
#define ILLEGAL_NAME    2
#define DIVIDE_ZERO    3
#define COMMENT_NOT_END 4
#define ILLEGAL_NUM    5
#define BAD_START_CHAR    6
#define LACK_SQUOTE    7
#define LACK_DQUOTE    8

// error message
extern const std::vector<std::string> zerrormsg;
// print error log
void print_error(int linenu, int index, int id, std::string info="");

#endif

/* author: dongchangzhang */
/* time: Sun 05 Mar 2017 12:00:59 PM CST */

#ifndef __ZERROR_H__
#define __ZERROR_H__

#include <string>
#include <vector>


// error id
#define NONE_DEFINE_SYMBOL 0
#define NONE_INPUT    1
#define ILLEGAL_NAME    2
#define DIVIDE_ZERO    3
// error message
extern const std::vector<std::string> zerrormsg;
// print error log
void print_error(int linenu, int id, std::string info="");

#endif

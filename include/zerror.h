/* author: dongchangzhang */
/* time: Sun 05 Mar 2017 12:00:59 PM CST */

#ifndef __ZERROR_H__
#define __ZERROR_H__

#include <string>
#include <vector>


// error id
#define NONE_INPUT    0
#define ILLEGAL_NAME    1
#define DIVIDE_ZERO    2
// error message
extern const std::vector<std::string> zerrormsg;
// print error log
void print_error(int linenu, int id);

#endif

/* author: dongchangzhang */
/* time: Sat 11 Mar 2017 11:24:09 PM CST */

#include "parser.h"

#include<algorithm>
#include<iostream>
#include<vector>
#include<string>

void Parser::run()
{
    Token token = tokenizer.next();
    std::cout << token.get_token() << std::endl;
    token = tokenizer.next();
    std::cout << token.get_token() << std::endl;
    token = tokenizer.next();
    std::cout << token.get_token() << std::endl;
    token = tokenizer.next();
    std::cout << token.get_token() << std::endl;
}

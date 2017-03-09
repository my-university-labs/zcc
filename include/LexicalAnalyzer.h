/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:39:51 PM CST */

#ifndef __LEXICAL_ANALYZER_H__
#define __LEXICAL_ANALYZER_H__

#include <fstream>
#include <string>
#include <regex>

#include "utils.h"

class LexicalAnalyzer {
    public:
        LexicalAnalyzer() : type(0), re_pattern(pattern), re_comment_end(comment_end), re_number(number) {  };
        LexicalAnalyzer(std::string f) : type(1), file(f),
        re_pattern(pattern), re_comment_end(comment_end), re_number(number) { in.open(f); };

        ~LexicalAnalyzer() { if(in) in.close(); }
        // input a file name when init this class
        ZToken next();
        // input a string
        bool isend() {
            return finished;
        }
    private:
        bool finished = false;

        int linenu = 0;

        int type = 0;

        ZToken token;

        std::string file;

        std::string line;

        std::ifstream in;

        std::string pattern = "(^[a-zA-Z_]+[a-zA-Z0-9_]*)|" // key word or id
            "(^0[xX]\\d+)|(^\\d+\\.?\\d*)|" // number
            "(^[*+-/=><&|!]+|^[()])|" // operator
            "(^[\\[\\]{};\"\'])"; // sepatator

        std::string comment_end = "\\*/";

        std::string number = "(^0[Xx]\\d+|(^\\d+\\.?\\d*))"; // number

        std::regex re_pattern;

        std::regex re_comment_end;

        std::regex re_number;

        void skip_ws();
        
        void ignore_comment();

        ZToken get_ch();

        ZToken get_string();

        ZToken deal_element(const std::string &element);

        ZToken do_next();

};

#endif



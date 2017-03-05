/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:39:51 PM CST */

#ifndef __LEXICAL_ANALYZER__
#define __LEXICAL_ANALYZER__

#include <fstream>
#include <string>

class LexicalAnalyzer {
    public:
        LexicalAnalyzer(std::string f) : file(f) {  }; 
        
        // delete comments and blank chars
        void preprocess();

        // do lexical analyze
        void analyze();

    private:
        std::string file;
        std::ifstream in; 
};

#endif



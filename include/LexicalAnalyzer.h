/* author: dongchangzhang */
/* time: Fri 03 Mar 2017 12:39:51 PM CST */

#ifndef __LEXICAL_ANALYZER_H__
#define __LEXICAL_ANALYZER_H__

#include <fstream>
#include <string>
#include <unordered_map>
#include <set>

#define WT_KEYWORD    1
#define WT_OPERATOR    2
#define WT_VALUE    3
#define WT_SEPARATOR    4
#define WT_IDENTIFIER    5

typedef int word_type

// a set save all key words of c language 
extern const std::unordered_map<std::string, int> keyword_table;
// all operators
extern const std::unordered_map<std::string, int> operator_table;
// all sepatators
extern const std::unordered_map<std::string, int> sepatator_table;

// all type;
extern const std::vector<std::string> token_table;

class LexicalAnalyzer {
    public:
        LexicalAnalyzer(std::string f) : file(f) {  }; 
        
        // do lexical analyze
        void analyze();

        void save_to_file(const string& name);

    private:
        std::string file;

        ifstream& ignore_comment(int &linenu, std::ifstream & in);

        word_type what_type(const std::string& s);

        bool is_keyword(const std::string& s);

        bool is_separator(const std::string& s);

        bool is_operator(const std::string& s);

        bool is_value(const std::string& s);

        bool is_identifier(const std::string& s);

        bool check_identifier(const std::string& s);
};

#endif



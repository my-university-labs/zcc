/* author: dongchangzhang */
/* time: Wed 22 Mar 2017 11:16:34 PM CST */

#ifndef SRC_PLUGIN_GRAMMERDEALER_H
#define SRC_PLUGIN_GRAMMERDEALER_H

#include "grammar.h"

#include <map>
#include <fstream>
#include <string>
#include <vector>

class GrammerDealer {
    public:
        GrammerDealer(std::string grammer_file) : file(grammer_file)  {  in.open(grammer_file); }
        ~GrammerDealer() { if (in) in.close(); }

        bool load_grammer();

        bool transform_grammer();

        void print_grammer(std::string out_file="grammer_output.txt");

    private:

        std::string file;
        std::ifstream in;
        // save grammers
        Grammar grammar;

};
#endif /* ifndef SSRC_PLUGIN_GRAMMERDEALER_H */

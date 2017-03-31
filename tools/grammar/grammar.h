/* author: dongchangzhang */
/* time: Mon 27 Mar 2017 07:30:04 PM CST */

#ifndef SRC_PLUGIN_GRAMMER_H
#define SRC_PLUGIN_GRAMMER_H

#include <string>
#include <map>
#include <vector>

class Grammar {
    public:
        Grammar() {}

        void insert(std::string &key, std::string &comment);

        std::vector<std::string> get_content(const std::string &key, const int id) const;

        void check() const;

    private:
        std::map<std::string, std::vector<std::vector<std::string>>> grammar;
};

#endif

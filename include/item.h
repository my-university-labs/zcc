/* author: dongchangzhang */
/* time: Thu 30 Mar 2017 11:32:53 PM CST */
#ifndef SRC_PLUGIN_GRAMMAR_H
#define SRC_PLUGIN_GRAMMAR_H

#include <string>
#include <vector>

class Item {
    public:
        Item(std::string &w, size_t i, size_t p) : which(w), index(i), production_size(p) {}

        Item(std::string &w, size_t i, size_t p, bool special) : Item(w, i, p), is_special(special) {}

        Item& operator=(const Item &item) {
            which = item.which;
            index = item.index;
            decimal_location = item.decimal_location;
            end_symbol = end_symbol;
        }

        bool move_decimal() {
           if (decimal_location < production_size) { ++decimal_location; return true; }
           else if (decimal_location == production_size) { 
               ++decimal_location; 
               had_end = false;
           }
           else return false;
        }

        bool is_end() const {
            return had_end;
        }
    private:
        /* which production */
        std::string which;
        /* the index of the production */
        size_t index;
        /* decimal before location */
        size_t decimal_location;

        size_t production_size;
        /* end symbols id */
        std::vector<int> end_symbol;

        bool had_end = false;

        bool is_special = false;
};

#endif

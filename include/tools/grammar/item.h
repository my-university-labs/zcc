/* author: dongchangzhang */
/* time: Thu 30 Mar 2017 11:32:53 PM CST */

// when deal grammar files (productions) and use grammar to make closure and go
// function ,
// this class used to save the item of every production

#ifndef SRC_PLUGIN_GRAMMAR_H
#define SRC_PLUGIN_GRAMMAR_H

#include "grammar.h"
#include "token.h"
#include "unstd.h"

#include <algorithm>
#include <string>
#include <vector>

class Item {
public:
    Item(const std::string& w, const size_t i, const int e, const size_t p)
        : which(w)
        , index(i)
        , end_symbol(e)
        , production_size(p)
        , decimal_location(0)
    {
    }

    Item& operator=(const Item& item)
    {
        which = item.which;
        index = item.index;
        decimal_location = item.decimal_location;
        end_symbol = end_symbol;
        return *this;
    }

    bool operator==(const Item& item) const
    {
        return (which == item.which && index == item.index
            && end_symbol == item.end_symbol);
    }

    inline bool move_decimal();

    inline bool is_end() const { return had_end; }

    int get_end_symbol() const { return end_symbol; }

    inline Token after_decimal(Grammar& grammar) const;

    inline std::vector<Token> for_first(Grammar& grammar);

    inline bool next_is_state(Grammar& grammar);

    inline std::string get_which() const { return which; }

    inline int get_index() const { return index; }

private:
    /* which production */
    std::string which;
    /* the index of the production */
    size_t index;
    /* end symbols id */
    int end_symbol = END_STATE;

    size_t production_size;

    size_t decimal_location;

    bool had_end = false;
};

bool Item::move_decimal()
{
    if (decimal_location < production_size) {
        ++decimal_location;
        return true;
    } else if (decimal_location == production_size) {
        ++decimal_location;
        had_end = false;
    } else {
        return false;
    }
    return false;
}

Token Item::after_decimal(Grammar& grammar) const
{
    std::vector<Token> p = grammar.get_production(which, index);
    return p.at(decimal_location);
}

std::vector<Token> Item::for_first(Grammar& grammar)
{
    std::vector<Token> p = grammar.get_production(which, index);
    std::vector<Token> r;
    for (size_t i = decimal_location + 1; i < p.size(); ++i) {
        r.push_back(p.at(i));
    }
    Token token(end_symbol);
    r.push_back(token);
    return r;
}

bool Item::next_is_state(Grammar& grammar)
{
    if (had_end)
        return false;
    Token token = after_decimal(grammar);
    if (token.is_state_token())
        return true;
    else
        return false;
}

// overwrite hash<Item>
namespace std {
template <>
struct hash<Item> {
    typedef size_t return_type;
    typedef Item argument_type;
    size_t operator()(const Item& i) const
    {
        return hash<string>()(i.get_which()) ^ hash<int>()(i.get_index()) ^ hash<int>()(i.get_end_symbol());
    };
};
}

#endif

#ifndef PLUGIN_ADDR_CODES_H
#define PLUGIN_ADDR_CODES_H

#include <ostream>
#include <string>

#define IS_OP 11
#define IS_INT 21
#define IS_CHAR 31
#define IS_FLOAT 41

size_t timer_code_increase();

class CodeManager {
public:
    typedef struct {
        int element_type;
        int ivalue;
        float fvalue;
        std::string svalue;

    } code_element;

public:
    CodeManager() = default;

    size_t generate_code();
    void print_code(size_t id);

private:
};

std::ostream& operator<<(std::ostream& os, CodeManager::code_element& ce);
#endif
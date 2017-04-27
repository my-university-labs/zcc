#ifndef PLUGIN_CODE_H
#define PLUGIN_CODE_H

#include <iostream>

class Code {
public:
    Code() = default;

private:
    size_t value1;
    size_t value2;
    size_t option;
};

std::ostream& operator<<(std::ostream& os, Code& code);

#endif
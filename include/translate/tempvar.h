#ifndef TRANSLATE_TEMP_VAR_H
#define TRANSLATE_TEMP_VAR_H

class TempCreater {
public:
    TempCreater()
        : temp_timer(0);
    size_t create_temp_var();

private:
    static size_t temp_timer;
};
#endif
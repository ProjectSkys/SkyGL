#pragma once

#include <skygl/basic/common.h>

NS_SKY_GL_BEG

class Key {
public:
    int id;
    int code;
    int action;
    int mode;
public:
    Key(int id, int code = 0, int action = 0, int mode = 0)
        : id(id), code(code), action(action), mode(mode) {}
    operator int() const {
        return id;
    }
};

NS_SKY_GL_END

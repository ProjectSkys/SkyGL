#pragma once

#include <skygl/common.h>
#include <skygl/types.h>

#include <exception>
#include <sstream>

NS_SKY_GL_BEG

class GLException: public std::exception {
private:
    String _what;
public:
    GLException(KStringRef tag, KStringRef msg) {
        std::stringstream ss;
        ss << "[" << tag << "]:\n";
        ss << msg;
        _what = ss.str();
    }
    const char* what() const noexcept {
        return _what.c_str();
    }
};

NS_SKY_GL_END

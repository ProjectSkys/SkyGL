#pragma once

#include "skygl/basic/common.h"
#include "skygl/basic/types.h"

#include <fstream>
#include <streambuf>

#include <zlog.h>

NS_SKY_GL_BEG

#define SKY_PROPERTY(type, name) \
    protected: \
        type name; \
    public: \
        void set##name(const type& _) { \
            name = _; \
        } \
        type get##name() const { \
            return name; \
        } \
    private:

#define SKY_PROPERTY_R(type, name) \
    protected: \
        type name; \
    public: \
        type get##name() const { \
            return name; \
        } \
    private:

#define SKY_PROPERTY_W(type, name) \
    protected: \
        type name; \
    public: \
        void set##name(const type& _) { \
            name = _; \
        } \
    private:

String readFileFromPath(KStringRef path) {
    std::ifstream file(path);
    if (!file) {
        throw GLException("readFileFromPath", "Fail to read file: " + path);
    }
    // ensures ifstream objects can throw exceptions
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    String content((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    return content;
}

NS_SKY_GL_END

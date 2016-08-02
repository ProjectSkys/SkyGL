#pragma once

#include <skygl/common.h>
#include <skygl/types.h>

#include <fstream>
#include <streambuf>

#include <zlog.h>

NS_SKY_GL_BEG

String readFileFromPath(KStringRef path) {
    std::ifstream file(path);
    // ensures ifstream objects can throw exceptions
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    String content((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    return content;
}

NS_SKY_GL_END

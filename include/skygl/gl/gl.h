#pragma once

#include <skygl/basic/common.h>
#include <skygl/basic/types.h>
#include <skygl/calc/color.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

NS_SKY_GL_BEG

inline void glGet(Enum pname, Bool* params) {
    glGetBooleanv(pname, params);
}
inline void glGet(Enum pname, Double* params) {
    glGetDoublev(pname, params);
}
inline void glGet(Enum pname, Float* params) {
    glGetFloatv(pname, params);
}
inline void glGet(Enum pname, Int* params) {
    glGetIntegerv(pname, params);
}

inline void glToggle(Enum pname) {
    Bool enabled;
    glGet(pname, &enabled);
    if (enabled) glDisable(pname);
    else glEnable(pname);
}

NS_SKY_GL_END

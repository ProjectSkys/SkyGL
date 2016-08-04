#pragma once

#include <skygl/common.h>
#include <skygl/types.h>
#include <skygl/color.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

NS_SKY_GL_BEG

inline void glClearColorBuffer(ClampF r = 0, ClampF g = 0, ClampF b = 0, ClampF a = 1) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

inline void glClearColorBuffer(const ColorRGB& rgb) {
    glClearColorBuffer(rgb.r, rgb.g, rgb.b);
}

inline void glClearColorBuffer(const ColorRGBA& rgba) {
    glClearColorBuffer(rgba.r, rgba.g, rgba.b, rgba.a);
}

NS_SKY_GL_END

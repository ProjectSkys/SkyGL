#pragma once

#include <skygl/common.h>
#include <skygl/types.h>
#include <skygl/color.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

NS_SKY_GL_BEG

void glClearColor(const ColorRGB& rgb) {
    glClearColor(rgb.r, rgb.g, rgb.b, 1.0f);
}

void glClearColor(const ColorRGBA& rgba) {
    glClearColor(rgba.r, rgba.g, rgba.b, rgba.a);
}

NS_SKY_GL_END

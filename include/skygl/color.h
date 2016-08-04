#pragma once

#include <skygl/common.h>
#include <skygl/types.h>

#include <glm/glm.hpp>

NS_SKY_GL_BEG

using ColorRGB = glm::tvec3<ClampF, glm::mediump>;
using ColorRGBA = glm::tvec4<ClampF, glm::mediump>;

namespace Color {
#define DECLARE_COLOR(color) \
    extern const ColorRGB color; \
    extern const ColorRGBA color##A;
    DECLARE_COLOR(Black)
    DECLARE_COLOR(Blue)
    DECLARE_COLOR(Green)
    DECLARE_COLOR(Red)
    DECLARE_COLOR(White)
#undef DECLARE_COLOR
};

NS_SKY_GL_END
